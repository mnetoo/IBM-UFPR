module Funcionarios where

-- Exercicio 5

baseFuncionario :: Int -> (String, String, Float)
baseFuncionario x
    | x == 1 = ("Carlos",  "TI",      5000.0)
    | x == 2 = ("Mariana", "RH",      3800.0)
    | x == 3 = ("Pedro",   "TI",      6200.0)
    | x == 4 = ("Lucia",   "Vendas",  4100.0)
    | x == 5 = ("Rafael",  "Vendas",  3500.0)
    | otherwise = ("ninguem", "", 0.0)

-- a) Crie apelidos de tipo para Nome, Departamento, Salario, Funcionario e Empresa.
type NomeFuncionario = String
type DepartamentoFuncionario = String
type SalarioFuncionario = Float
type Funcionario = (NomeFuncionario, DepartamentoFuncionario, SalarioFuncionario)
type Empresa = [Funcionario]

-- b) Crie uma função recursiva para formar uma Empresa com os elementos da função base.
criarEmpresa :: Int -> Empresa
criarEmpresa x
    | x < 1 = []
    | x > 5 = criarEmpresa (x - 1)
    | otherwise = [baseFuncionario x] ++ criarEmpresa (x - 1)

-- c) Escreva uma função recursiva de alta ordem reajuste :: Empresa -> (Salario -> Salario) -> Empresa 
-- que aplique uma função de transformação no salário de cada funcionário, retornando a empresa atualizada.
aumentaSalario :: SalarioFuncionario -> SalarioFuncionario
aumentaSalario x = x + 1000.0

reajuste :: Empresa -> (SalarioFuncionario -> SalarioFuncionario) -> Empresa
reajuste [] _ = []
reajuste ((nome, departamento, salario):t) f = (nome, departamento, f salario) : reajuste t f

-- d) Usando gerador de lista, escreva uma função funcionariosPorDepto :: Empresa -> Departamento -> [Nome] 
-- que retorne apenas os nomes dos funcionários de um departamento específico.
funcionariosPorDepto :: Empresa -> DepartamentoFuncionario -> [NomeFuncionario]
funcionariosPorDepto emp depto = [nome | (nome, departamento, salario) <- emp, departamento == depto]

-- e) Escreva uma função recursiva maiorSalario :: Empresa -> Salario que retorne o maior salário da empresa.
maiorSalario :: Empresa -> SalarioFuncionario
maiorSalario [] = 0.0
maiorSalario ((_, _, s):t) = if(s > maior) then s else maior
    where
        maior = maiorSalario t