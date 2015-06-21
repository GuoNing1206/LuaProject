----------------------------------------------------
-- 堆排序 Demo 参考资料:《算法》Page206
----------------------------------------------------
MaxPQ = 
{
	----------------------------------------------------
	-- 比较函数
	----------------------------------------------------
	CompareFunc = function(a, b)
		return a < b
	end,
	
	----------------------------------------------------
	-- 判断是否是空堆 
	----------------------------------------------------
	IsEmpty = function(self)
		return self:Count() == 0
	end,
	
	----------------------------------------------------
	-- 插入数据
	----------------------------------------------------
	Insert = function(self, value)
		self.Key[self:Count() + 1] = value
		self:Swim(self:Count())
	end,
	
	----------------------------------------------------
	-- 比较两个位置的数据
	----------------------------------------------------
	Less = function(self, i, j)
		return self.CompareFunc(self.Key[i], self.Key[j])
	end,
	
	----------------------------------------------------
	-- 交换两个位置的数据
	----------------------------------------------------
	Exch = function(self, i, j)
		local temp = self.Key[i]
		self.Key[i] = self.Key[j]
		self.Key[j] = temp
	end,

	----------------------------------------------------
	-- 数据总数
	----------------------------------------------------
	Count = function(self)
		return #(self.Key)
	end,

	----------------------------------------------------
	-- 数据上浮
	----------------------------------------------------
	Swim = function(self, k)
		while k > 1 and self:Less(math.floor(k / 2), k) do
			self:Exch(math.floor(k / 2), k)
			k = math.floor(k / 2)
		end
	end,

	----------------------------------------------------
	-- 数据下沉 将self.Key数组左侧N个元素作为操作堆
	----------------------------------------------------
	Sink = function(self, k, N)
		local count = N or #(self.Key)
		while 2 * k <= count do
			local j = 2 * k
			if j < count and self:Less(j, j + 1) then
				j = j + 1
			end
			if not self:Less(k, j) then
				break
			end
			self:Exch(k, j)
			k = j
		end
	end,

	----------------------------------------------------
	-- 删除最大值, 并将其返回
	----------------------------------------------------
	DelMax = function(self)
		local iMax = self.Key[1]
		self:Exch(1, #(self.Key))
		self.Key[#(self.Key)] = nil
		self:Sink(1)
		return iMax
	end,

	----------------------------------------------------
	-- 新建一个二叉堆
	----------------------------------------------------
	NewPQ = function(array)
		local pq = {Key = array or {}}
		setmetatable(pq, MaxPQ)
		return pq
	end,
	
	----------------------------------------------------
	-- 堆排序
	--------------------------	--------------------------
	Sort = function(arr, sortFunc)
		-- 设置比较函数
		MaxPQ.CompareFunc = sortFunc
		local pq = MaxPQ.NewPQ(arr)
	
		local N = pq:Count()
		
		-- 堆的构造
		for k = math.floor(N / 2), 1, -1 do
			pq:Sink(k)
		end
		
		-- 下沉排序
		while N > 1 do
			pq:Exch(1, N)
			N = N - 1
			pq:Sink(1, N)
		end
	end,
	
	----------------------------------------------------
	-- 判断一个数组是否是已经排好序的 order: 升序? 降序?
	----------------------------------------------------
	SortTest = function(sortedTable, order)
		if order then
			for i = 1, #sortedTable - 1 do
				if sortedTable[i] > sortedTable[i + 1] then
					print("排序失败!\n")
					return
				end
			end
			print("排序成功 ^_^\n")
		else
			for i = 1, #sortedTable - 1 do
				if sortedTable[i] < sortedTable[i + 1] then
					print("排序失败!\n")
					return
				end
			end
			print("排序成功 ^_^\n")
		end
	end,
	
	----------------------------------------------------
	-- 打印二叉堆数组
	----------------------------------------------------
	Print = function(self)
		for i = 1, #self.Key do
			io.write(self.Key[i].." ")
		end
		io.write("\n")
	end
}
MaxPQ.__index = MaxPQ

function PrintArray(arr)
	for i = 1, #arr do
		io.write(arr[i].." ")
	end
	io.write("\n")
end
----------------------------------------------------
-- 将一个数组数据打乱
----------------------------------------------------
function ArrayShuffle(a, times)
	math.randomseed(os.time())
	for i = 1, times do
		local i = math.random(#a)
		local j = math.random(#a)
		local temp = a[i]
		a[i] = a[j]
		a[j] = temp
	end
end

----------------------------------------------------
-- 创建一个随机数组, 元素为 1 ~ size 互不相同的数字
----------------------------------------------------
function NewRandomArray(size)
	local arr = {}
	for i = 1, size do
		arr[#arr + 1] = i
	end
	ArrayShuffle(arr, size)
	return arr
end

----------------------------------------------------
-- 测试函数
----------------------------------------------------
function Test()
	print("堆排序 Demo 参考资料:《算法》Page206")

	local result = NewRandomArray(23)
	io.write("初始序列: ")
	PrintArray(result)

	-- 排序操作
	MaxPQ.Sort(result, function(a, b) return a < b end)
	
	io.write("排序结果: ")
	PrintArray(result)
	
	MaxPQ.SortTest(result, true)
end

Test()