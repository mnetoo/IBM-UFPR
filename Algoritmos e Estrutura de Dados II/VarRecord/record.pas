program alg2;

const maxCliente = 5;

type
		tipoCliente = record
				nome: string;
				valor: real;
				end;
var

	cadastro: array [1..maxCliente] of tipoCliente;
	soma: real;
	i, n: integer;

begin
	
	soma:= 0.00;

	writeln('Insira a quantidade de clientes que dejeja cadastrar: ');
	readln(n);

	for i:= 1 to maxCliente do
	begin
		readln(cadastro[i].nome);
		readln(cadastro[i].valor);
	end;

	for i:= 1 to maxCliente do
		soma:= soma + cadastro[i].valor;
	
	writeln;
	writeln('Media: ', soma/maxCliente:0:2);
	writeln;

	for i:= 1 to n do
	begin
			writeln('Nome: ', cadastro[i].nome, ' - ','Valor da Compra: ', cadastro[i].valor:0:2);
			writeln;
	end;
end.
