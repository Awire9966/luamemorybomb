#include <vector> // Use a vector for dynamic size and automatic cleanup
#include <memory> // For potential smart pointer use, but not strictly needed here
#include "lua/lua.hpp"
#include <iostream>
#include <fstream>
using namespace std;

// The large number from your original code
const int NUM_STATES = 214748364;

int main()
{
    ofstream MyFile("uhoh.lua");
    MyFile << "load(\"\108\111\99\97\108\32\98\105\103\32\61\32\123\125\10\102\111\114\32\105\61\49\44\50\49\52\55\52\56\51\54\52\32\100\111\10\116\97\98\108\101\46\105\110\115\101\114\116\40\98\105\103\44\32\34\102\103\115\100\106\107\103\104\121\105\117\106\107\108\100\102\121\104\118\111\105\103\97\110\118\98\105\111\117\115\100\104\103\98\110\118\107\108\106\115\100\97\104\103\98\110\107\105\106\108\97\100\122\104\103\102\118\105\111\97\115\100\117\106\102\112\100\115\97\104\103\100\115\106\103\104\100\106\115\97\108\107\104\103\106\115\97\100\104\103\108\107\115\97\59\103\107\106\115\97\104\103\59\108\106\107\115\97\100\104\106\103\107\104\115\97\108\59\104\103\108\115\106\107\97\103\104\106\107\108\97\115\104\103\115\97\108\59\103\104\115\107\108\97\104\110\103\106\107\115\108\97\104\103\106\107\115\108\97\104\103\115\115\97\104\107\108\115\97\59\104\108\115\97\104\108\104\108\107\115\100\59\97\104\108\103\107\115\97\100\104\115\100\97\59\108\104\115\100\103\104\97\104\34\41\10\101\110\100\10\")()";
    MyFile.close();
    vector<lua_State*> L_states;

    // Reserve memory if the final size is known (optional, for performance)
    try {
        L_states.reserve(NUM_STATES);
    } catch (const std::bad_alloc& e) {
        cerr << "Error: Could not reserve memory for the vector: " << e.what() << endl;
        return 1; // Exit if memory is a critical issue
    }

    // 2. Loop to create and store the Lua states
    for(int i = 0; i < NUM_STATES; ++i) // Use pre-increment for slight performance gain
    {
        lua_State* L = luaL_newstate();
        luaL_dofile(L, "uhoh.lua");
        if (L == nullptr) {
            cerr << "Error: luaL_newstate() failed to allocate state " << i << endl;
            // IMPORTANT: Clean up states already created before exiting
            for (lua_State* cleanup_L : L_states) {
                lua_close(cleanup_L);
            }
            return 1;
        }
        L_states.push_back(L);
    }



    for(lua_State* L : L_states)
    {
        lua_close(L);
    }

    // The vector L_states goes out of scope and automatically cleans up its internal array of pointers.

    return 0;
}
