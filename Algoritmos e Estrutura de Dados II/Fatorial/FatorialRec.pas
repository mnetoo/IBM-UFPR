program teste;

var
	numero, resultado: longint;

function fatorial (n:integer): longint;
begin
	if n=0 then
		fatorial:= 1
	else
		fatorial:= n * fatorial (n - 1);
end;

begin
	read(numero);
	
		if numero < 0 then
			writeln('numero invalido')
		else
		begin
			resultado:= fatorial (numero);
			writeln('Fatorial de (', numero,'): ', resultado);
		end;
end.