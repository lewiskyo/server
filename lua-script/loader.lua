local str = ...

local args = {}
for word in string.gmatch(str, "%S+") do
	table.insert(args, word)
end

local main_file_name = args[1]


local main = loadfile(main_file_name)

if not main then
	error(table.concat(err, "\n"))
end

package.path , LUA_PATH = LUA_PATH
package.cpath , LUA_CPATH = LUA_CPATH

main(select(2, table.unpack(args)))

