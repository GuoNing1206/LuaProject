--[[
for i = 1, 9 do
	local line = {}
	for j = 1, i do
		line[#line + 1] = j.."*"..i.."="..i*j
	end
	print(unpack(line))
end
--]]

local output = io.stdout

for i = 1, 9 do
	for j = 1, i do
		output:write(j.."*"..i.."="..i*j.."\t")
--		io.write(j.."*"..i.."="..i*j.."\t")
	end
	output:write("\r\n")
end
