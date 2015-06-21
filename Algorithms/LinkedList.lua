List = {}

function List.New()
	return {first = 0, last = -1};
end

function List.PushFirst(list, value)
	local first = list.first - 1;
	list.first = first;
	list[first] = value;
end

function List.PushLast(list, value)
	local last = list.last + 1;
	list.last = last;
	list[last] = value;
end

function List.PopFirst(list)
	local first = list.first;
	if first > list.last then error("list is empty") end
	local value = list[first];
	list[first] = nil;
	list.first = first + 1;
	return value;
end

function List.PopLast(list)
	local last = list.last;
	if list.first > last then error("list is empty") end
	local value = list[last];
	list[last] = nil;
	list.last = last - 1;
	return value;
end

function PrintList(list)
	print("***************************");
	print("*", "Index", "Value");
	for i = list.first, list.last do
		print("*", i, list[i]);
	end
	print("***************************");
end

myList = List.New();
List.PushFirst(myList, "ttt");
List.PushFirst(myList, "aaa");
PrintList(myList);

List.PushLast(myList, "last");
PrintList(myList);
