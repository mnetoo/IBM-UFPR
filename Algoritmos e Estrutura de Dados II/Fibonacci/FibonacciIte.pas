program FibonacciIterativo;

var
    n, i: integer;
    a, b, temp: integer;

function fibonacciIterativo(n: integer): integer;
var
    i: integer;
    a, b, temp: integer;

begin
    if (n = 0) then
        fibonacciIterativo := 0
    else if (n = 1) then
        fibonacciIterativo := 1
    else
    begin
        a := 0;
        b := 1;
            for i := 2 to n do
            begin
                temp := a + b;
                a := b;
                b := temp;
            end;
            fibonacciIterativo := b;
    end;
end;

begin
    readln(n);
    writeln(fibonacciIterativo(n));
end.