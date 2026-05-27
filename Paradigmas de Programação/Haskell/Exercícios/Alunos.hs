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


-- ----------------------------------------------------------------------------------------------------------------

-- b) Escreva uma função mediaAluno :: Aluno -> Double que calcule a média aritmética duas notas sem usar 
-- divisão direta — some as notas recursivamente com uma função auxiliar
-- somarDois :: Double -> Double -> Double e divida ao final.
somarDois :: NotaAluno -> NotaAluno -> NotaAluno
somarDois x y = x + y

mediaAluno :: Aluno -> NotaAluno
mediaAluno (_,0.0,0.0) = 0.0
mediaAluno (_, n1, n2) = (somarDois n1 n2) / fromIntegral 2 

-- c) Escreva uma função recursiva quantosAprovados :: [Aluno] -> Int que conte quantos alunos têm média maior 
-- ou igual a 6.0. Utilize mediaAluno internamente.
quantosAprovados :: Turma -> Int
quantosAprovados [] = 0
quantosAprovados (h:t)
    | mediaAluno h > 6.0 = 1 + quantosAprovados t
    | otherwise = quantosAprovados t

-- d) Escreva uma função recursiva listarReprovados :: [Aluno] -> [NomeAluno] que retorne apenas os nomes dos 
-- alunos com média menor que 6.0.
listarReprovados :: Turma -> [NomeAluno]
listarReprovados [] = []
listarReprovados ((nome, n1, n2):t) =
    if(mediaAluno (nome, n1, n2) < 6.0) then nome : listarReprovados t
    else listarReprovados t 

-- e) Escreva uma função recursiva de alta ordem classificar :: (Aluno -> Bool) -> [Aluno] -> [NomeAluno] que 
-- receba um predicado e retorne os nomes dos alunos que o satisfazem. Reescreva listarReprovados usando classificar.
notaAlta :: Aluno -> Bool
notaAlta a
    | mediaAluno a > 8.0 = True
    | otherwise = False

classificar :: (Aluno -> Bool) -> Turma -> [NomeAluno]
classificar _ [] = []
classificar f ((nome, n1, n2):t)
    | notaAlta (nome, n1, n2) == True = [nome] ++ classificar f t 
    | otherwise = classificar f t