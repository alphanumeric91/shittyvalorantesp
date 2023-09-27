#include "check.h"
#include "Func.h"
#include "xor.h"

uintptr_t virtualaddy;

#define MEDreadwyy CTL_CODE(FILE_DEVICE_UNKNOWN, 0x07D, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define MEDbab3 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x09A, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define Scode_security 0x85b3e20

typedef struct _readwrite {
	INT32 security;
	INT32 process_id;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
	BOOLEAN write;
} rw, * prw;


typedef struct _ba {
	INT32 security;
	INT32 process_id;
	ULONGLONG* address;
} ba, * pba;

typedef struct _ga {
	INT32 security;
	ULONGLONG* address;
} ga, * pga;

typedef struct _SYSTEM_BIGPOOL_ENTRY
{
	union {
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	};
	ULONG_PTR SizeInBytes;
	union {
		UCHAR Tag[4];
		ULONG TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, *PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION {
	ULONG Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[ANYSIZE_ARRAY];
} SYSTEM_BIGPOOL_INFORMATION, *PSYSTEM_BIGPOOL_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBigPoolInformation = 0x42
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI* pNtQuerySystemInformation)(
	IN _SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID                   SystemInformation,
	IN ULONG                    SystemInformationLength,
	OUT PULONG                  ReturnLength
	);

__forceinline auto query_bigpools() -> PSYSTEM_BIGPOOL_INFORMATION
{
	static const pNtQuerySystemInformation NtQuerySystemInformation =
		(pNtQuerySystemInformation)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQuerySystemInformation");

	DWORD length = 0;
	DWORD size = 0;
	LPVOID heap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 0);
	heap = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, heap, 0xFF);
	NTSTATUS ntLastStatus = NtQuerySystemInformation(SystemBigPoolInformation, heap, 0x30, &length);
	heap = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, heap, length + 0x1F);
	size = length;
	ntLastStatus = NtQuerySystemInformation(SystemBigPoolInformation, heap, size, &length);

	return reinterpret_cast<PSYSTEM_BIGPOOL_INFORMATION>(heap);
}
__forceinline auto retrieve_guarded() -> uintptr_t
{
	auto pool_information = query_bigpools();
	uintptr_t guarded = 0;

	if (pool_information)
	{
		auto count = pool_information->Count;
		for (auto i = 0ul; i < count; i++)
		{
			SYSTEM_BIGPOOL_ENTRY* allocation_entry = &pool_information->AllocatedInfo[i];
			const auto virtual_address = (PVOID)((uintptr_t)allocation_entry->VirtualAddress & ~1ull);
			if (allocation_entry->NonPaged && allocation_entry->SizeInBytes == 0x200000)
				if (guarded == 0 && allocation_entry->TagUlong == 'TnoC')
					guarded = reinterpret_cast<uintptr_t>(virtual_address);
		}
	}

	return guarded;
}

namespace mem {
	HANDLE driver_handle;
	INT32 process_id;

	bool find_driver() {
		driver_handle = CreateFileW(_(L"\\\\.\\\MedusaNewCom"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
			return false;

		return true;
	}

	void read_physical(PVOID address, PVOID buffer, DWORD size) {
		_readwrite arguments = { 0 };

		arguments.security = Scode_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.write = FALSE;

		DeviceIoControl(driver_handle, MEDreadwyy, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void write_physical(PVOID address, PVOID buffer, DWORD size) {
		_readwrite arguments = { 0 };

		arguments.security = Scode_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.write = TRUE;

		DeviceIoControl(driver_handle, MEDreadwyy, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	uintptr_t find_image() {
		uintptr_t image_address = { NULL };
		_ba arguments = { NULL };

		arguments.security = Scode_security;
		arguments.process_id = process_id;
		arguments.address = (ULONGLONG*)&image_address;

		DeviceIoControl(driver_handle, MEDbab3, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

		return image_address;
	}

	INT32 find_process(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					process_id = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);
		return process_id;
	}

}

template <typename T>
T read2(uint64_t address) {
	T buffer{ };
	mem::read_physical((PVOID)address, &buffer, sizeof(T));
	if (check::is_guarded(buffer))
	{
		buffer = check::validate_pointer(buffer);
	}

	return buffer;
}

template <typename T>
T read(uint64_t address) {
	T buffer{ };
	mem::read_physical((PVOID)address, &buffer, sizeof(T));

	return buffer;
}

template <typename T>
T write(uint64_t address, T buffer) {

	mem::write_physical((PVOID)address, &buffer, sizeof(T));
	return buffer;
}