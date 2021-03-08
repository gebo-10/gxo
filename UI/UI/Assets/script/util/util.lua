Util={}
-- 交集
function Util.Intersection(t1, t2)
    local ret = {}
    for k, v1 in pairs(t1) do
        local equal = false
        for k, v2 in pairs(t2) do
            if v1 == v2 then
                equal = true
                break
            end
        end
        if equal then
            table.insert(ret, v1)
        end
    end
    return ret
end
--差集
function Util.Diff(tb1,tb2)
	local dt1={}
	for i,v in ipairs(tb1) do
		dt1[v]=true
	end
	local dt2={}
	for i,v in ipairs(tb2) do
		dt2[v]=true
	end

	local d1={}
	for i,v in ipairs(tb1) do
		if not dt2[v] then
			table.insert(d1,v)
		end
	end

	local d2={}
	for i,v in ipairs(tb2) do
		if not dt1[v] then
			table.insert(d2,v)
		end
	end

	return d1,d2
end


function logt( tbl , level, filteDefault)
  local msg = ""
  filteDefault = filteDefault or true --默认过滤关键字（DeleteMe, _class_type）
  level = level or 1
  local indent_str = ""
  for i = 1, level do
    indent_str = indent_str.."  "
  end

  print(indent_str .. "{")
  for k,v in pairs(tbl) do
    if filteDefault then
      if k ~= "_class_type" and k ~= "DeleteMe" then
        local item_str = string.format("%s%s = %s", indent_str .. " ",tostring(k), tostring(v))
        print(item_str)
        if type(v) == "table" then
          logt(v, level + 1)
        end
      end
    else
      local item_str = string.format("%s%s = %s", indent_str .. " ",tostring(k), tostring(v))
      print(item_str)
      if type(v) == "table" then
        logt(v, level + 1)
      end
    end
  end
  print(indent_str .. "}")
end

function print_lua_table (lua_table, indent)
	indent = indent or 0
	for k, v in pairs(lua_table) do
		if type(k) == "string" then
			k = string.format("%q", k)
		end
		local szSuffix = ""
		if type(v) == "table" then
			szSuffix = "{"
		end
		local szPrefix = string.rep("    ", indent)
		formatting = szPrefix.."["..k.."]".." = "..szSuffix
		if type(v) == "table" then
			print(formatting)
			print_lua_table(v, indent + 1)
			print(szPrefix.."},")
		else
			local szValue = ""
			if type(v) == "string" then
				szValue = string.format("%q", v)
			else
				szValue = tostring(v)
			end
			print(formatting..szValue..",")
		end
	end
end

function log(...)
	print(...)
end