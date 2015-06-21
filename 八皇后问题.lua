local N = 5

-- check whether position(n, c) is free from attacks
local function IsPlaceOK(a, n, c)
	for i = 1, n - 1 do
		if (a[i] == c) or
			 (a[i] - i == c - n) or
			 (a[i] + i == c + n) then
			return false
		end
	end
	return true
end

-- print a board
local function PrintSolution(a)
	for i = 1, N do
		for j = 1, N do
			io.write(a[i] == j and "X" or "-", " ")
		end
		io.write("\r\n")
	end
	io.write("\r\n")
end

-- add to board 'a' all queens from 'n' to 'N'
local function AddQueen(a, n)
	if n > N then
		PrintSolution(a)
	else
		for c = 1, N do
			if IsPlaceOK(a, n ,c) then
				a[n] = c
				AddQueen(a, n + 1)
			end
		end
	end
end

-- run the program
AddQueen({}, 1)