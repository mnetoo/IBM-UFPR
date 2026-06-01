module PrimeiroPrograma where

-- a. Base de dados
-- Nessa parte, declare 5 funções para representar os números reais de uma sequência. Por exemplo:
num :: Int -> Float
num 1 = 5.0
num 2 = 10.0
num 3 = 15.0
num 4 = 20.0
num 5 = 25.0

-- b. Função recursiva (soma)
-- Implemente uma função recursiva para somar todos os números retornados
-- pelas funções da base de dados (num 1 + num 2 + ... num 5). A função, de
-- preferência, não deve usar if-then-else ou guardas.
soma :: Int -> Float
soma 0 = 0.0
soma x = num x + soma(x - 1)

-- c. Função (media)
-- Implemente uma função (não recursiva) para calcular a média dos números
-- retornados pelas funções da base de dados. Dica: a função fromIntegral
-- converte um inteiro para real e possui a seguinte assinatura de tipo:
-- fromIntegral :: Int -> Float
media :: Int -> Float
media n = soma n / fromIntegral n