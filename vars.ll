declare void @printInt(i32)
define i32 @main() {
	%a = alloca i32
	store i32 2, i32* %a
	%d = alloca i32
	store i32 5, i32* %d
	%f = alloca i32
	store i32 4, i32* %f
	%load_0 = load i32, i32* %a
	%c = alloca i32
	store i32 %load_0, i32* %c
	%load_1 = load i32, i32* %a
	call void @printInt(i32 %load_1)
	%load_2 = load i32, i32* %c
	%1 = mul i32 %load_2, 5
	%e = alloca i32
	store i32 %1, i32* %e
	store i32 4, i32* %a
	%load_3 = load i32, i32* %a
	call void @printInt(i32 %load_3)
	%load_4 = load i32, i32* %d
	call void @printInt(i32 %load_4)
	%load_5 = load i32, i32* %f
	call void @printInt(i32 %load_5)
	%load_6 = load i32, i32* %c
	call void @printInt(i32 %load_6)
	%load_7 = load i32, i32* %e
	call void @printInt(i32 %load_7)
	ret i32 0
}