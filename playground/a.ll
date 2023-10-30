declare void @printInt(i32)
define i32 @main() {
	%a = alloca i32
	store i32 42, i32* %a
	%load_a = load i32, i32* %a
	call void @printInt(i32 %load_a)
	%1 = mul i32 2, 3
	%2 = sub i32 6, %1
	%3 = add i32 3, %2
	call void @printInt(i32 %3)
	ret i32 0
}