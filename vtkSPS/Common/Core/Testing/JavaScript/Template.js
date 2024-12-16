// Import the function from wasmLoader.js
import loadSpsCommonCoreTestWasmModule from './spsCommonCoreTest.js';

// Automatically populated
import TestSpsVersion from './TestSpsVersion.js';

// Define the options object
const options = {
    print: function () {
        const text = Array.prototype.slice.call(arguments).join(' ');
        console.info(text);
    },
    printErr: function () {
        const text = Array.prototype.slice.call(arguments).join(' ');
        console.error(text);
    }
};
var wasmModule
let nErrors = 0;
// Main function to load and use the WASM module
async function main() {
    try {
        // Load the WASM module
        wasmModule = await loadSpsCommonCoreTestWasmModule(options);

        // Automatically populated
        TestSpsVersion();
        
    } catch (error) {
	nErrors++;
        console.error("An error occurred:", error);
    }
}

// Execute the main function
await main();

// Can be captured with $?
process.exit(nErrors == 0 ? 0 : 1);
