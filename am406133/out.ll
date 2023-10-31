declare void @printInt(i32)
define i32 @main() {
	%a = alloca i32
	store i32 1, i32* %a
	%load_0 = load i32, i32* %a
	%load_1 = load i32, i32* %a
	%1 = add i32 %load_0, %load_1
	store i32 %1, i32* %a
	%load_2 = load i32, i32* %a
	%load_3 = load i32, i32* %a
	%2 = add i32 %load_2, %load_3
	store i32 %2, i32* %a
	%load_4 = load i32, i32* %a
	call void @printInt(i32 %load_4)
	ret i32 0
}