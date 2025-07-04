program pf;

type
	vetor = array [1..200] of integer;

var
	N, j, k, tamA, tamB, tamU, tamI, tamDS: integer;
	A, B, U, I, DS: vetor;

procedure lerVetor(var v: vetor; var tam: integer);
var
	i: integer;
begin
	read(tam);
	for i := 1 to tam do
		read(v[i]);
end;

procedure uniao(var A: vetor; tamA: integer; var B: vetor; tamB: integer; var U: vetor; var tamU: integer);
var
	i, j, k: integer;
	existe: boolean;
begin
	tamU := 0;

	// Copiando elementos de A para U
	for i := 1 to tamA do
	begin
		U[i] := A[i];
		tamU := tamU + 1;
	end;

	// Copiando elementos de B para U, sem repetir os elementos já em U
	for j := 1 to tamB do
	begin
		existe := false;
		for k := 1 to tamU do
		begin
			if B[j] = U[k] then
			begin
				existe := true;
				break;
			end;
		end;

		if not existe then
		begin
			U[tamU + 1] := B[j];
			tamU := tamU + 1;
		end;
	end;
end;

procedure interseccao(var A: vetor; tamA: integer; var B: vetor; tamB: integer; var I: vetor; var tamI: integer);
var
	k, j: integer;
begin
	tamI := 0;

	for k := 1 to tamA do
	begin
		for j := 1 to tamB do
		begin
			if A[k] = B[j] then
			begin
				if (tamI = 0) or (A[k] <> I[tamI]) then
				begin
					tamI := tamI + 1;
					I[tamI] := A[k];
				end;
				break;
			end;
		end;
	end;
end;

procedure diferencaSimetrica(var A: vetor; tamA: integer; var B: vetor; tamB: integer; var DS: vetor; var tamDS: integer);
var
	i, j: integer;
	existe: boolean;
begin
	tamDS := 0;

	// Adicionando elementos de A que não estão em B
	for i := 1 to tamA do
	begin
		existe := false;
		for j := 1 to tamB do
		begin
			if A[i] = B[j] then
			begin
				existe := true;
				break;
			end;
		end;

		if not existe then
		begin
			tamDS := tamDS + 1;
			DS[tamDS] := A[i];
		end;
	end;

	// Adicionando elementos de B que não estão em A
	for j := 1 to tamB do
	begin
		existe := false;
		for i := 1 to tamA do
		begin
			if B[j] = A[i] then
			begin
				existe := true;
				break;
			end;
		end;

		if not existe then
		begin
			tamDS := tamDS + 1;
			DS[tamDS] := B[j];
		end;
	end;
end;

begin
	read(N);

	for j:= 1 to N do 
	begin	
		lerVetor(A, tamA);
		lerVetor(B, tamB);
		uniao(A, tamA, B, tamB, U, tamU);
			writeln;
			write('A uniao B: ');
			for k:= 1 to tamU do
				write(U[k], ' ');
			writeln;
			writeln;
		
		interseccao(A, tamA, B, tamB, I, tamI);
			writeln;
			write('A interseccao B: ');
			for k:= 1 to tamI do
				write(I[k], ' ');
			writeln;
			writeln;
		
		diferencaSimetrica(A, tamA, B, tamB, DS, tamDS);
			writeln;
			write('Diferenca Simetrica entre A e B: ');
			for k:= 1 to tamDS do
				write(DS[k], ' ');
			writeln;
			writeln;
	end;
end.
