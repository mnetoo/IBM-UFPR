module PrimeiroPrograma where

-- Base de Dados
num :: Int -> Float
num 1 = 5.0
num 2 = 10.0
num 3 = 15.0
num 4 = 20.0
num 5 = 25.0

-- Função de Soma Recursiva
soma :: Int -> Float
soma 0 = 0.0
soma x = num x + soma(x - 1)

-- Função de Média
media :: Int -> Float
media n = soma n / fromIntegral n