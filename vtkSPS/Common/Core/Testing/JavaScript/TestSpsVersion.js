export function TestSpsVersion(wasmModule) {
    var retval = 0;
    try {
        var version = wasmModule.spsVersion();
    }
    catch {
        retval = 1;
    }
    return retval;
}
