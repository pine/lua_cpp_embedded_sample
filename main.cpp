#include <iostream>
#include <lua.hpp>

int sum(lua_State* n);
int sum_impl(int n);

int main() {
    lua_State* L = luaL_newstate();

    // 標準ライブラリを読み込み
    luaL_openlibs(L);

    // 外部ファイルを読み込み
    luaL_loadfile(L, "main.lua");
    lua_pcall(L, 0, LUA_MULTRET, 0);

    // 関数を呼び出す
    std::cout << "C -> Lua: ";
    lua_getglobal(L, "hello");
    lua_pushstring(L, "Lua");
    lua_pcall(L, 1, LUA_MULTRET, 0);

    // Lua から C の関数を呼び出す
    std::cout << "Lua -> C: ";
    lua_register(L, "sum", sum); // 登録
    lua_getglobal(L, "fast_sum");
    lua_pcall(L, 0, 1, 0);

    int r = lua_tonumber(L, -1); // 結果を取得
    lua_pop(L, 1);

    std::cout << r << std::endl;

    // 終了処理
    lua_close(L);

    return 0;
}

int sum(lua_State* L) {
    // 引数を受け取る
    int n = lua_tointeger(L, 1);

    // 戻り値を格納
    lua_pushinteger(L, sum_impl(n));

    // 戻り値の数を返す
    return 1;
}

// 実際の演算処理
int sum_impl(int n) {
    int sum = 0;

    for (int i = 1; i <= n; ++i) {
        sum += i;
    }

    return sum;
}

// vim: se et ts=4 sw=4 sts=4 ft=cpp :
