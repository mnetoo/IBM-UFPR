program rec;

var
    n: integer;

function fibonacci(n: integer):integer;
begin
        if (n = 0) then
            fibonacci:= 0
        else if (n = 1) or (n = 2) then
            fibonacci:= 1
        else
            fibonacci:= fibonacci(n - 1) + fibonacci(n - 2);
end;

begin
    read(n);
    writeln(fibonacci(n));
end.