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
	%b = alloca i32
	store i32 4, i32* %b
	%load_b = load i32, i32* %b
	%4 = mul i32 3, %load_b
	%load_b = load i32, i32* %b
	%5 = sdiv i32 %4, %load_b
	call void @printInt(i32 %5)
	ret i32 0
}