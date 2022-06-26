#include <Windows.h>

#include "infinity.h"

#pragma region Proxy
struct secur32_dll {
	HMODULE dll;
	FARPROC oAcceptSecurityContext;
	FARPROC oAcquireCredentialsHandleA;
	FARPROC oAcquireCredentialsHandleW;
	FARPROC oAddCredentialsA;
	FARPROC oAddCredentialsW;
	FARPROC oAddSecurityPackageA;
	FARPROC oAddSecurityPackageW;
	FARPROC oApplyControlToken;
	FARPROC oChangeAccountPasswordA;
	FARPROC oChangeAccountPasswordW;
	FARPROC oCloseLsaPerformanceData;
	FARPROC oCollectLsaPerformanceData;
	FARPROC oCompleteAuthToken;
	FARPROC oCredMarshalTargetInfo;
	FARPROC oCredUnmarshalTargetInfo;
	FARPROC oDecryptMessage;
	FARPROC oDeleteSecurityContext;
	FARPROC oDeleteSecurityPackageA;
	FARPROC oDeleteSecurityPackageW;
	FARPROC oEncryptMessage;
	FARPROC oEnumerateSecurityPackagesA;
	FARPROC oEnumerateSecurityPackagesW;
	FARPROC oExportSecurityContext;
	FARPROC oFreeContextBuffer;
	FARPROC oFreeCredentialsHandle;
	FARPROC oGetComputerObjectNameA;
	FARPROC oGetComputerObjectNameW;
	FARPROC oGetSecurityUserInfo;
	FARPROC oGetUserNameExA;
	FARPROC oGetUserNameExW;
	FARPROC oImpersonateSecurityContext;
	FARPROC oImportSecurityContextA;
	FARPROC oImportSecurityContextW;
	FARPROC oInitSecurityInterfaceA;
	FARPROC oInitSecurityInterfaceW;
	FARPROC oInitializeSecurityContextA;
	FARPROC oInitializeSecurityContextW;
	FARPROC oLsaCallAuthenticationPackage;
	FARPROC oLsaConnectUntrusted;
	FARPROC oLsaDeregisterLogonProcess;
	FARPROC oLsaEnumerateLogonSessions;
	FARPROC oLsaFreeReturnBuffer;
	FARPROC oLsaGetLogonSessionData;
	FARPROC oLsaLogonUser;
	FARPROC oLsaLookupAuthenticationPackage;
	FARPROC oLsaRegisterLogonProcess;
	FARPROC oLsaRegisterPolicyChangeNotification;
	FARPROC oLsaUnregisterPolicyChangeNotification;
	FARPROC oMakeSignature;
	FARPROC oOpenLsaPerformanceData;
	FARPROC oQueryContextAttributesA;
	FARPROC oQueryContextAttributesW;
	FARPROC oQueryCredentialsAttributesA;
	FARPROC oQueryCredentialsAttributesW;
	FARPROC oQuerySecurityContextToken;
	FARPROC oQuerySecurityPackageInfoA;
	FARPROC oQuerySecurityPackageInfoW;
	FARPROC oRevertSecurityContext;
	FARPROC oSaslAcceptSecurityContext;
	FARPROC oSaslEnumerateProfilesA;
	FARPROC oSaslEnumerateProfilesW;
	FARPROC oSaslGetContextOption;
	FARPROC oSaslGetProfilePackageA;
	FARPROC oSaslGetProfilePackageW;
	FARPROC oSaslIdentifyPackageA;
	FARPROC oSaslIdentifyPackageW;
	FARPROC oSaslInitializeSecurityContextA;
	FARPROC oSaslInitializeSecurityContextW;
	FARPROC oSaslSetContextOption;
	FARPROC oSealMessage;
	FARPROC oSeciAllocateAndSetCallFlags;
	FARPROC oSeciAllocateAndSetIPAddress;
	FARPROC oSeciFreeCallContext;
	FARPROC oSecpFreeMemory;
	FARPROC oSecpTranslateName;
	FARPROC oSecpTranslateNameEx;
	FARPROC oSetContextAttributesA;
	FARPROC oSetContextAttributesW;
	FARPROC oSetCredentialsAttributesA;
	FARPROC oSetCredentialsAttributesW;
	FARPROC oSspiCompareAuthIdentities;
	FARPROC oSspiCopyAuthIdentity;
	FARPROC oSspiDecryptAuthIdentity;
	FARPROC oSspiEncodeAuthIdentityAsStrings;
	FARPROC oSspiEncodeStringsAsAuthIdentity;
	FARPROC oSspiEncryptAuthIdentity;
	FARPROC oSspiExcludePackage;
	FARPROC oSspiFreeAuthIdentity;
	FARPROC oSspiGetTargetHostName;
	FARPROC oSspiIsAuthIdentityEncrypted;
	FARPROC oSspiLocalFree;
	FARPROC oSspiMarshalAuthIdentity;
	FARPROC oSspiPrepareForCredRead;
	FARPROC oSspiPrepareForCredWrite;
	FARPROC oSspiUnmarshalAuthIdentity;
	FARPROC oSspiValidateAuthIdentity;
	FARPROC oSspiZeroAuthIdentity;
	FARPROC oTranslateNameA;
	FARPROC oTranslateNameW;
	FARPROC oUnsealMessage;
	FARPROC oVerifySignature;
} secur32;

extern "C" {
	FARPROC PA = 0;
	int runASM();

	void fAcceptSecurityContext() { PA = secur32.oAcceptSecurityContext; runASM(); }
	void fAcquireCredentialsHandleA() { PA = secur32.oAcquireCredentialsHandleA; runASM(); }
	void fAcquireCredentialsHandleW() { PA = secur32.oAcquireCredentialsHandleW; runASM(); }
	void fAddCredentialsA() { PA = secur32.oAddCredentialsA; runASM(); }
	void fAddCredentialsW() { PA = secur32.oAddCredentialsW; runASM(); }
	void fAddSecurityPackageA() { PA = secur32.oAddSecurityPackageA; runASM(); }
	void fAddSecurityPackageW() { PA = secur32.oAddSecurityPackageW; runASM(); }
	void fApplyControlToken() { PA = secur32.oApplyControlToken; runASM(); }
	void fChangeAccountPasswordA() { PA = secur32.oChangeAccountPasswordA; runASM(); }
	void fChangeAccountPasswordW() { PA = secur32.oChangeAccountPasswordW; runASM(); }
	void fCloseLsaPerformanceData() { PA = secur32.oCloseLsaPerformanceData; runASM(); }
	void fCollectLsaPerformanceData() { PA = secur32.oCollectLsaPerformanceData; runASM(); }
	void fCompleteAuthToken() { PA = secur32.oCompleteAuthToken; runASM(); }
	void fCredMarshalTargetInfo() { PA = secur32.oCredMarshalTargetInfo; runASM(); }
	void fCredUnmarshalTargetInfo() { PA = secur32.oCredUnmarshalTargetInfo; runASM(); }
	void fDecryptMessage() { PA = secur32.oDecryptMessage; runASM(); }
	void fDeleteSecurityContext() { PA = secur32.oDeleteSecurityContext; runASM(); }
	void fDeleteSecurityPackageA() { PA = secur32.oDeleteSecurityPackageA; runASM(); }
	void fDeleteSecurityPackageW() { PA = secur32.oDeleteSecurityPackageW; runASM(); }
	void fEncryptMessage() { PA = secur32.oEncryptMessage; runASM(); }
	void fEnumerateSecurityPackagesA() { PA = secur32.oEnumerateSecurityPackagesA; runASM(); }
	void fEnumerateSecurityPackagesW() { PA = secur32.oEnumerateSecurityPackagesW; runASM(); }
	void fExportSecurityContext() { PA = secur32.oExportSecurityContext; runASM(); }
	void fFreeContextBuffer() { PA = secur32.oFreeContextBuffer; runASM(); }
	void fFreeCredentialsHandle() { PA = secur32.oFreeCredentialsHandle; runASM(); }
	void fGetComputerObjectNameA() { PA = secur32.oGetComputerObjectNameA; runASM(); }
	void fGetComputerObjectNameW() { PA = secur32.oGetComputerObjectNameW; runASM(); }
	void fGetSecurityUserInfo() { PA = secur32.oGetSecurityUserInfo; runASM(); }
	void fGetUserNameExA() { PA = secur32.oGetUserNameExA; runASM(); }
	void fGetUserNameExW() { PA = secur32.oGetUserNameExW; runASM(); }
	void fImpersonateSecurityContext() { PA = secur32.oImpersonateSecurityContext; runASM(); }
	void fImportSecurityContextA() { PA = secur32.oImportSecurityContextA; runASM(); }
	void fImportSecurityContextW() { PA = secur32.oImportSecurityContextW; runASM(); }
	void fInitSecurityInterfaceA() { PA = secur32.oInitSecurityInterfaceA; runASM(); }
	void fInitSecurityInterfaceW() { PA = secur32.oInitSecurityInterfaceW; runASM(); }
	void fInitializeSecurityContextA() { PA = secur32.oInitializeSecurityContextA; runASM(); }
	void fInitializeSecurityContextW() { PA = secur32.oInitializeSecurityContextW; runASM(); }
	void fLsaCallAuthenticationPackage() { PA = secur32.oLsaCallAuthenticationPackage; runASM(); }
	void fLsaConnectUntrusted() { PA = secur32.oLsaConnectUntrusted; runASM(); }
	void fLsaDeregisterLogonProcess() { PA = secur32.oLsaDeregisterLogonProcess; runASM(); }
	void fLsaEnumerateLogonSessions() { PA = secur32.oLsaEnumerateLogonSessions; runASM(); }
	void fLsaFreeReturnBuffer() { PA = secur32.oLsaFreeReturnBuffer; runASM(); }
	void fLsaGetLogonSessionData() { PA = secur32.oLsaGetLogonSessionData; runASM(); }
	void fLsaLogonUser() { PA = secur32.oLsaLogonUser; runASM(); }
	void fLsaLookupAuthenticationPackage() { PA = secur32.oLsaLookupAuthenticationPackage; runASM(); }
	void fLsaRegisterLogonProcess() { PA = secur32.oLsaRegisterLogonProcess; runASM(); }
	void fLsaRegisterPolicyChangeNotification() { PA = secur32.oLsaRegisterPolicyChangeNotification; runASM(); }
	void fLsaUnregisterPolicyChangeNotification() { PA = secur32.oLsaUnregisterPolicyChangeNotification; runASM(); }
	void fMakeSignature() { PA = secur32.oMakeSignature; runASM(); }
	void fOpenLsaPerformanceData() { PA = secur32.oOpenLsaPerformanceData; runASM(); }
	void fQueryContextAttributesA() { PA = secur32.oQueryContextAttributesA; runASM(); }
	void fQueryContextAttributesW() { PA = secur32.oQueryContextAttributesW; runASM(); }
	void fQueryCredentialsAttributesA() { PA = secur32.oQueryCredentialsAttributesA; runASM(); }
	void fQueryCredentialsAttributesW() { PA = secur32.oQueryCredentialsAttributesW; runASM(); }
	void fQuerySecurityContextToken() { PA = secur32.oQuerySecurityContextToken; runASM(); }
	void fQuerySecurityPackageInfoA() { PA = secur32.oQuerySecurityPackageInfoA; runASM(); }
	void fQuerySecurityPackageInfoW() { PA = secur32.oQuerySecurityPackageInfoW; runASM(); }
	void fRevertSecurityContext() { PA = secur32.oRevertSecurityContext; runASM(); }
	void fSaslAcceptSecurityContext() { PA = secur32.oSaslAcceptSecurityContext; runASM(); }
	void fSaslEnumerateProfilesA() { PA = secur32.oSaslEnumerateProfilesA; runASM(); }
	void fSaslEnumerateProfilesW() { PA = secur32.oSaslEnumerateProfilesW; runASM(); }
	void fSaslGetContextOption() { PA = secur32.oSaslGetContextOption; runASM(); }
	void fSaslGetProfilePackageA() { PA = secur32.oSaslGetProfilePackageA; runASM(); }
	void fSaslGetProfilePackageW() { PA = secur32.oSaslGetProfilePackageW; runASM(); }
	void fSaslIdentifyPackageA() { PA = secur32.oSaslIdentifyPackageA; runASM(); }
	void fSaslIdentifyPackageW() { PA = secur32.oSaslIdentifyPackageW; runASM(); }
	void fSaslInitializeSecurityContextA() { PA = secur32.oSaslInitializeSecurityContextA; runASM(); }
	void fSaslInitializeSecurityContextW() { PA = secur32.oSaslInitializeSecurityContextW; runASM(); }
	void fSaslSetContextOption() { PA = secur32.oSaslSetContextOption; runASM(); }
	void fSealMessage() { PA = secur32.oSealMessage; runASM(); }
	void fSeciAllocateAndSetCallFlags() { PA = secur32.oSeciAllocateAndSetCallFlags; runASM(); }
	void fSeciAllocateAndSetIPAddress() { PA = secur32.oSeciAllocateAndSetIPAddress; runASM(); }
	void fSeciFreeCallContext() { PA = secur32.oSeciFreeCallContext; runASM(); }
	void fSecpFreeMemory() { PA = secur32.oSecpFreeMemory; runASM(); }
	void fSecpTranslateName() { PA = secur32.oSecpTranslateName; runASM(); }
	void fSecpTranslateNameEx() { PA = secur32.oSecpTranslateNameEx; runASM(); }
	void fSetContextAttributesA() { PA = secur32.oSetContextAttributesA; runASM(); }
	void fSetContextAttributesW() { PA = secur32.oSetContextAttributesW; runASM(); }
	void fSetCredentialsAttributesA() { PA = secur32.oSetCredentialsAttributesA; runASM(); }
	void fSetCredentialsAttributesW() { PA = secur32.oSetCredentialsAttributesW; runASM(); }
	void fSspiCompareAuthIdentities() { PA = secur32.oSspiCompareAuthIdentities; runASM(); }
	void fSspiCopyAuthIdentity() { PA = secur32.oSspiCopyAuthIdentity; runASM(); }
	void fSspiDecryptAuthIdentity() { PA = secur32.oSspiDecryptAuthIdentity; runASM(); }
	void fSspiEncodeAuthIdentityAsStrings() { PA = secur32.oSspiEncodeAuthIdentityAsStrings; runASM(); }
	void fSspiEncodeStringsAsAuthIdentity() { PA = secur32.oSspiEncodeStringsAsAuthIdentity; runASM(); }
	void fSspiEncryptAuthIdentity() { PA = secur32.oSspiEncryptAuthIdentity; runASM(); }
	void fSspiExcludePackage() { PA = secur32.oSspiExcludePackage; runASM(); }
	void fSspiFreeAuthIdentity() { PA = secur32.oSspiFreeAuthIdentity; runASM(); }
	void fSspiGetTargetHostName() { PA = secur32.oSspiGetTargetHostName; runASM(); }
	void fSspiIsAuthIdentityEncrypted() { PA = secur32.oSspiIsAuthIdentityEncrypted; runASM(); }
	void fSspiLocalFree() { PA = secur32.oSspiLocalFree; runASM(); }
	void fSspiMarshalAuthIdentity() { PA = secur32.oSspiMarshalAuthIdentity; runASM(); }
	void fSspiPrepareForCredRead() { PA = secur32.oSspiPrepareForCredRead; runASM(); }
	void fSspiPrepareForCredWrite() { PA = secur32.oSspiPrepareForCredWrite; runASM(); }
	void fSspiUnmarshalAuthIdentity() { PA = secur32.oSspiUnmarshalAuthIdentity; runASM(); }
	void fSspiValidateAuthIdentity() { PA = secur32.oSspiValidateAuthIdentity; runASM(); }
	void fSspiZeroAuthIdentity() { PA = secur32.oSspiZeroAuthIdentity; runASM(); }
	void fTranslateNameA() { PA = secur32.oTranslateNameA; runASM(); }
	void fTranslateNameW() { PA = secur32.oTranslateNameW; runASM(); }
	void fUnsealMessage() { PA = secur32.oUnsealMessage; runASM(); }
	void fVerifySignature() { PA = secur32.oVerifySignature; runASM(); }
}

void setupFunctions() {
	secur32.oAcceptSecurityContext = GetProcAddress(secur32.dll, "AcceptSecurityContext");
	secur32.oAcquireCredentialsHandleA = GetProcAddress(secur32.dll, "AcquireCredentialsHandleA");
	secur32.oAcquireCredentialsHandleW = GetProcAddress(secur32.dll, "AcquireCredentialsHandleW");
	secur32.oAddCredentialsA = GetProcAddress(secur32.dll, "AddCredentialsA");
	secur32.oAddCredentialsW = GetProcAddress(secur32.dll, "AddCredentialsW");
	secur32.oAddSecurityPackageA = GetProcAddress(secur32.dll, "AddSecurityPackageA");
	secur32.oAddSecurityPackageW = GetProcAddress(secur32.dll, "AddSecurityPackageW");
	secur32.oApplyControlToken = GetProcAddress(secur32.dll, "ApplyControlToken");
	secur32.oChangeAccountPasswordA = GetProcAddress(secur32.dll, "ChangeAccountPasswordA");
	secur32.oChangeAccountPasswordW = GetProcAddress(secur32.dll, "ChangeAccountPasswordW");
	secur32.oCloseLsaPerformanceData = GetProcAddress(secur32.dll, "CloseLsaPerformanceData");
	secur32.oCollectLsaPerformanceData = GetProcAddress(secur32.dll, "CollectLsaPerformanceData");
	secur32.oCompleteAuthToken = GetProcAddress(secur32.dll, "CompleteAuthToken");
	secur32.oCredMarshalTargetInfo = GetProcAddress(secur32.dll, "CredMarshalTargetInfo");
	secur32.oCredUnmarshalTargetInfo = GetProcAddress(secur32.dll, "CredUnmarshalTargetInfo");
	secur32.oDecryptMessage = GetProcAddress(secur32.dll, "DecryptMessage");
	secur32.oDeleteSecurityContext = GetProcAddress(secur32.dll, "DeleteSecurityContext");
	secur32.oDeleteSecurityPackageA = GetProcAddress(secur32.dll, "DeleteSecurityPackageA");
	secur32.oDeleteSecurityPackageW = GetProcAddress(secur32.dll, "DeleteSecurityPackageW");
	secur32.oEncryptMessage = GetProcAddress(secur32.dll, "EncryptMessage");
	secur32.oEnumerateSecurityPackagesA = GetProcAddress(secur32.dll, "EnumerateSecurityPackagesA");
	secur32.oEnumerateSecurityPackagesW = GetProcAddress(secur32.dll, "EnumerateSecurityPackagesW");
	secur32.oExportSecurityContext = GetProcAddress(secur32.dll, "ExportSecurityContext");
	secur32.oFreeContextBuffer = GetProcAddress(secur32.dll, "FreeContextBuffer");
	secur32.oFreeCredentialsHandle = GetProcAddress(secur32.dll, "FreeCredentialsHandle");
	secur32.oGetComputerObjectNameA = GetProcAddress(secur32.dll, "GetComputerObjectNameA");
	secur32.oGetComputerObjectNameW = GetProcAddress(secur32.dll, "GetComputerObjectNameW");
	secur32.oGetSecurityUserInfo = GetProcAddress(secur32.dll, "GetSecurityUserInfo");
	secur32.oGetUserNameExA = GetProcAddress(secur32.dll, "GetUserNameExA");
	secur32.oGetUserNameExW = GetProcAddress(secur32.dll, "GetUserNameExW");
	secur32.oImpersonateSecurityContext = GetProcAddress(secur32.dll, "ImpersonateSecurityContext");
	secur32.oImportSecurityContextA = GetProcAddress(secur32.dll, "ImportSecurityContextA");
	secur32.oImportSecurityContextW = GetProcAddress(secur32.dll, "ImportSecurityContextW");
	secur32.oInitSecurityInterfaceA = GetProcAddress(secur32.dll, "InitSecurityInterfaceA");
	secur32.oInitSecurityInterfaceW = GetProcAddress(secur32.dll, "InitSecurityInterfaceW");
	secur32.oInitializeSecurityContextA = GetProcAddress(secur32.dll, "InitializeSecurityContextA");
	secur32.oInitializeSecurityContextW = GetProcAddress(secur32.dll, "InitializeSecurityContextW");
	secur32.oLsaCallAuthenticationPackage = GetProcAddress(secur32.dll, "LsaCallAuthenticationPackage");
	secur32.oLsaConnectUntrusted = GetProcAddress(secur32.dll, "LsaConnectUntrusted");
	secur32.oLsaDeregisterLogonProcess = GetProcAddress(secur32.dll, "LsaDeregisterLogonProcess");
	secur32.oLsaEnumerateLogonSessions = GetProcAddress(secur32.dll, "LsaEnumerateLogonSessions");
	secur32.oLsaFreeReturnBuffer = GetProcAddress(secur32.dll, "LsaFreeReturnBuffer");
	secur32.oLsaGetLogonSessionData = GetProcAddress(secur32.dll, "LsaGetLogonSessionData");
	secur32.oLsaLogonUser = GetProcAddress(secur32.dll, "LsaLogonUser");
	secur32.oLsaLookupAuthenticationPackage = GetProcAddress(secur32.dll, "LsaLookupAuthenticationPackage");
	secur32.oLsaRegisterLogonProcess = GetProcAddress(secur32.dll, "LsaRegisterLogonProcess");
	secur32.oLsaRegisterPolicyChangeNotification = GetProcAddress(secur32.dll, "LsaRegisterPolicyChangeNotification");
	secur32.oLsaUnregisterPolicyChangeNotification = GetProcAddress(secur32.dll, "LsaUnregisterPolicyChangeNotification");
	secur32.oMakeSignature = GetProcAddress(secur32.dll, "MakeSignature");
	secur32.oOpenLsaPerformanceData = GetProcAddress(secur32.dll, "OpenLsaPerformanceData");
	secur32.oQueryContextAttributesA = GetProcAddress(secur32.dll, "QueryContextAttributesA");
	secur32.oQueryContextAttributesW = GetProcAddress(secur32.dll, "QueryContextAttributesW");
	secur32.oQueryCredentialsAttributesA = GetProcAddress(secur32.dll, "QueryCredentialsAttributesA");
	secur32.oQueryCredentialsAttributesW = GetProcAddress(secur32.dll, "QueryCredentialsAttributesW");
	secur32.oQuerySecurityContextToken = GetProcAddress(secur32.dll, "QuerySecurityContextToken");
	secur32.oQuerySecurityPackageInfoA = GetProcAddress(secur32.dll, "QuerySecurityPackageInfoA");
	secur32.oQuerySecurityPackageInfoW = GetProcAddress(secur32.dll, "QuerySecurityPackageInfoW");
	secur32.oRevertSecurityContext = GetProcAddress(secur32.dll, "RevertSecurityContext");
	secur32.oSaslAcceptSecurityContext = GetProcAddress(secur32.dll, "SaslAcceptSecurityContext");
	secur32.oSaslEnumerateProfilesA = GetProcAddress(secur32.dll, "SaslEnumerateProfilesA");
	secur32.oSaslEnumerateProfilesW = GetProcAddress(secur32.dll, "SaslEnumerateProfilesW");
	secur32.oSaslGetContextOption = GetProcAddress(secur32.dll, "SaslGetContextOption");
	secur32.oSaslGetProfilePackageA = GetProcAddress(secur32.dll, "SaslGetProfilePackageA");
	secur32.oSaslGetProfilePackageW = GetProcAddress(secur32.dll, "SaslGetProfilePackageW");
	secur32.oSaslIdentifyPackageA = GetProcAddress(secur32.dll, "SaslIdentifyPackageA");
	secur32.oSaslIdentifyPackageW = GetProcAddress(secur32.dll, "SaslIdentifyPackageW");
	secur32.oSaslInitializeSecurityContextA = GetProcAddress(secur32.dll, "SaslInitializeSecurityContextA");
	secur32.oSaslInitializeSecurityContextW = GetProcAddress(secur32.dll, "SaslInitializeSecurityContextW");
	secur32.oSaslSetContextOption = GetProcAddress(secur32.dll, "SaslSetContextOption");
	secur32.oSealMessage = GetProcAddress(secur32.dll, "SealMessage");
	secur32.oSeciAllocateAndSetCallFlags = GetProcAddress(secur32.dll, "SeciAllocateAndSetCallFlags");
	secur32.oSeciAllocateAndSetIPAddress = GetProcAddress(secur32.dll, "SeciAllocateAndSetIPAddress");
	secur32.oSeciFreeCallContext = GetProcAddress(secur32.dll, "SeciFreeCallContext");
	secur32.oSecpFreeMemory = GetProcAddress(secur32.dll, "SecpFreeMemory");
	secur32.oSecpTranslateName = GetProcAddress(secur32.dll, "SecpTranslateName");
	secur32.oSecpTranslateNameEx = GetProcAddress(secur32.dll, "SecpTranslateNameEx");
	secur32.oSetContextAttributesA = GetProcAddress(secur32.dll, "SetContextAttributesA");
	secur32.oSetContextAttributesW = GetProcAddress(secur32.dll, "SetContextAttributesW");
	secur32.oSetCredentialsAttributesA = GetProcAddress(secur32.dll, "SetCredentialsAttributesA");
	secur32.oSetCredentialsAttributesW = GetProcAddress(secur32.dll, "SetCredentialsAttributesW");
	secur32.oSspiCompareAuthIdentities = GetProcAddress(secur32.dll, "SspiCompareAuthIdentities");
	secur32.oSspiCopyAuthIdentity = GetProcAddress(secur32.dll, "SspiCopyAuthIdentity");
	secur32.oSspiDecryptAuthIdentity = GetProcAddress(secur32.dll, "SspiDecryptAuthIdentity");
	secur32.oSspiEncodeAuthIdentityAsStrings = GetProcAddress(secur32.dll, "SspiEncodeAuthIdentityAsStrings");
	secur32.oSspiEncodeStringsAsAuthIdentity = GetProcAddress(secur32.dll, "SspiEncodeStringsAsAuthIdentity");
	secur32.oSspiEncryptAuthIdentity = GetProcAddress(secur32.dll, "SspiEncryptAuthIdentity");
	secur32.oSspiExcludePackage = GetProcAddress(secur32.dll, "SspiExcludePackage");
	secur32.oSspiFreeAuthIdentity = GetProcAddress(secur32.dll, "SspiFreeAuthIdentity");
	secur32.oSspiGetTargetHostName = GetProcAddress(secur32.dll, "SspiGetTargetHostName");
	secur32.oSspiIsAuthIdentityEncrypted = GetProcAddress(secur32.dll, "SspiIsAuthIdentityEncrypted");
	secur32.oSspiLocalFree = GetProcAddress(secur32.dll, "SspiLocalFree");
	secur32.oSspiMarshalAuthIdentity = GetProcAddress(secur32.dll, "SspiMarshalAuthIdentity");
	secur32.oSspiPrepareForCredRead = GetProcAddress(secur32.dll, "SspiPrepareForCredRead");
	secur32.oSspiPrepareForCredWrite = GetProcAddress(secur32.dll, "SspiPrepareForCredWrite");
	secur32.oSspiUnmarshalAuthIdentity = GetProcAddress(secur32.dll, "SspiUnmarshalAuthIdentity");
	secur32.oSspiValidateAuthIdentity = GetProcAddress(secur32.dll, "SspiValidateAuthIdentity");
	secur32.oSspiZeroAuthIdentity = GetProcAddress(secur32.dll, "SspiZeroAuthIdentity");
	secur32.oTranslateNameA = GetProcAddress(secur32.dll, "TranslateNameA");
	secur32.oTranslateNameW = GetProcAddress(secur32.dll, "TranslateNameW");
	secur32.oUnsealMessage = GetProcAddress(secur32.dll, "UnsealMessage");
	secur32.oVerifySignature = GetProcAddress(secur32.dll, "VerifySignature");
}
#pragma endregion

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		char path[MAX_PATH];
		GetWindowsDirectoryA(path, sizeof(path));

		strcat_s(path, "\\System32\\secur32.dll");
		secur32.dll = LoadLibraryA(path);
		setupFunctions();
		
		Infinity::Entry();

		break;
	case DLL_PROCESS_DETACH:
		printf("library unloaded?!");
		FreeLibrary(secur32.dll);
		break;
	}
	return 1;
}
