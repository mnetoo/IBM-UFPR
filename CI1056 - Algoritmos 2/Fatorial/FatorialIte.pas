program fatorial;

var
    n: integer;

function fatorial(n: integer):longint;
var
    i: integer; resultado: longint;
begin
        if (n = 0) then
            fatorial:= 0
        else
            resultado:= 1;
            for i:= 2 to n do
                resultado:= resultado * i;
            fatorial:= resultado;
end;

begin
    read(n);
    writeln('Fatorial de (', n, '): ', fatorial(n));
end.