module Alunos where

-- Exercicio 3

baseAluno :: Int -> (String, Float, Float)
baseAluno x
    | x == 1 = ("Ana",    8.5, 7.0)
    | x == 2 = ("Bruno",  4.0, 5.5)
    | x == 3 = ("Carla",  9.0, 9.5)
    | x == 4 = ("Diego",  3.5, 4.0)
    | x == 5 = ("Elena",  6.0, 7.5)
    | otherwise = ("ninguem", 0.0, 0.0)

-- a) Crie apelidos de tipo para Nome, Nota, Aluno e Turma.
type NomeAluno = String
type NotaAluno = Float
type Aluno = (NomeAluno, NotaAluno, NotaAluno)
type Turma = [Aluno]

-- b) Crie uma função recursiva para formar uma Turma com os elementos da função base.
criarTurma :: Int -> Turma
criarTurma x =
    if(x < 1) then []
    else if(x > 5) then criarTurma (x - 1)
    else baseAluno x : criarTurma (x - 1)

-- c) Escreva uma função recursiva aprovados que receba uma Turma e retorne uma lista 
-- com o nome dos alunos cuja média das duas notas seja maior ou igual a 6.0.
aprovados :: Turma -> [NomeAluno]
aprovados [] = []
aprovados ((nome, n1, n2):t)
    | (n1 + n2) / 2 >= 6.0 = nome : aprovados t
    | otherwise = aprovados t

-- d) Escreva uma função recursiva de alta ordem processaNota :: Turma -> (Nota -> Nota) -> Turma 
-- que aplique uma função de transformação em ambas as notas de cada aluno, retornando a turma atualizada.
pontoExtra :: Float -> Float
pontoExtra x = x + 1.0

processaNota :: Turma -> (NotaAluno -> NotaAluno) -> Turma
processaNota [] _ = []
processaNota ((nome, n1, n2):t) f = (nome, f n1, f n2) : processaNota t f