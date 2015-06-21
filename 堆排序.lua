----------------------------------------------------
-- ������ Demo �ο�����:���㷨��Page206
----------------------------------------------------
MaxPQ = 
{
	----------------------------------------------------
	-- �ȽϺ���
	----------------------------------------------------
	CompareFunc = function(a, b)
		return a < b
	end,
	
	----------------------------------------------------
	-- �ж��Ƿ��ǿն� 
	----------------------------------------------------
	IsEmpty = function(self)
		return self:Count() == 0
	end,
	
	----------------------------------------------------
	-- ��������
	----------------------------------------------------
	Insert = function(self, value)
		self.Key[self:Count() + 1] = value
		self:Swim(self:Count())
	end,
	
	----------------------------------------------------
	-- �Ƚ�����λ�õ�����
	----------------------------------------------------
	Less = function(self, i, j)
		return self.CompareFunc(self.Key[i], self.Key[j])
	end,
	
	----------------------------------------------------
	-- ��������λ�õ�����
	----------------------------------------------------
	Exch = function(self, i, j)
		local temp = self.Key[i]
		self.Key[i] = self.Key[j]
		self.Key[j] = temp
	end,

	----------------------------------------------------
	-- ��������
	----------------------------------------------------
	Count = function(self)
		return #(self.Key)
	end,

	----------------------------------------------------
	-- �����ϸ�
	----------------------------------------------------
	Swim = function(self, k)
		while k > 1 and self:Less(math.floor(k / 2), k) do
			self:Exch(math.floor(k / 2), k)
			k = math.floor(k / 2)
		end
	end,

	----------------------------------------------------
	-- �����³� ��self.Key�������N��Ԫ����Ϊ������
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
	-- ɾ�����ֵ, �����䷵��
	----------------------------------------------------
	DelMax = function(self)
		local iMax = self.Key[1]
		self:Exch(1, #(self.Key))
		self.Key[#(self.Key)] = nil
		self:Sink(1)
		return iMax
	end,

	----------------------------------------------------
	-- �½�һ�������
	----------------------------------------------------
	NewPQ = function(array)
		local pq = {Key = array or {}}
		setmetatable(pq, MaxPQ)
		return pq
	end,
	
	----------------------------------------------------
	-- ������
	--------------------------	--------------------------
	Sort = function(arr, sortFunc)
		-- ���ñȽϺ���
		MaxPQ.CompareFunc = sortFunc
		local pq = MaxPQ.NewPQ(arr)
	
		local N = pq:Count()
		
		-- �ѵĹ���
		for k = math.floor(N / 2), 1, -1 do
			pq:Sink(k)
		end
		
		-- �³�����
		while N > 1 do
			pq:Exch(1, N)
			N = N - 1
			pq:Sink(1, N)
		end
	end,
	
	----------------------------------------------------
	-- �ж�һ�������Ƿ����Ѿ��ź���� order: ����? ����?
	----------------------------------------------------
	SortTest = function(sortedTable, order)
		if order then
			for i = 1, #sortedTable - 1 do
				if sortedTable[i] > sortedTable[i + 1] then
					print("����ʧ��!\n")
					return
				end
			end
			print("����ɹ� ^_^\n")
		else
			for i = 1, #sortedTable - 1 do
				if sortedTable[i] < sortedTable[i + 1] then
					print("����ʧ��!\n")
					return
				end
			end
			print("����ɹ� ^_^\n")
		end
	end,
	
	----------------------------------------------------
	-- ��ӡ���������
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
-- ��һ���������ݴ���
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
-- ����һ���������, Ԫ��Ϊ 1 ~ size ������ͬ������
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
-- ���Ժ���
----------------------------------------------------
function Test()
	print("������ Demo �ο�����:���㷨��Page206")

	local result = NewRandomArray(23)
	io.write("��ʼ����: ")
	PrintArray(result)

	-- �������
	MaxPQ.Sort(result, function(a, b) return a < b end)
	
	io.write("������: ")
	PrintArray(result)
	
	MaxPQ.SortTest(result, true)
end

Test()