------------------------------------------------
-- 阶乘
------------------------------------------------
function Fact(n)
	if n <= 0 then
		return 1
	else
		return n * Fact(n - 1)
	end
end

------------------------------------------------
-- 多项式求值 a[1]*x^3 + a[2]*x^2 + a[3]*x + a[4]
------------------------------------------------
function Polynomial(coeff, x)
	local y = coeff[1]
	for i = 2, #coeff do
		y = y * x + coeff[i]
	end
	return y
end

function NewPoly(coeff)
	return function(x)
		return Polynomial(coeff, x)
	end
end

------------------------------------------------
-- 
------------------------------------------------
function Test()
--	print("enter a number:")
--	a = io.read("*n")
--	print(Fact(a))

	local f = NewPoly{3, 0, 1}
	print(f(0))
	print(f(5))
	print(f(10))
end

Test()