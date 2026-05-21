module FuncoesDiversas where

calcularAjuste :: Double -> Double
calcularAjuste salario = salario + (salario * 0.25)

calcularMedia :: Double -> Double -> Double -> Double -> Double -> Double -> Double
calcularMedia n1 p1 n2 p2 n3 p3 = ((n1 * p1) + (n2 * p2) + (n3 * p3)) / (p1 + p2 + p3)

converterTemperatura :: Double -> Double
converterTemperatura celcius = celcius * (9.0 / 5.0) + 32.0

calcularIdade :: Int -> Int
calcularIdade idade = 2032 - idade

calcularMinutos :: Int -> Int -> Int
calcularMinutos hora minuto = (hora * 60) + minuto

calcularSomaQuadrados :: Int -> Int -> Int -> Int
calcularSomaQuadrados x y z = (x * x) + (y * y) + (z * z)

verificaParidade :: Int -> String
verificaParidade x
    | mod x 2 == 0 = "PAR"
    | otherwise = "IMPAR"

verificaDivisibilidade :: Int -> Int -> String
verificaDivisibilidade x y
    | mod x y == 0 = "divisivel"
    | otherwise = "indivisivel"

calcularSalario :: Double -> Double
calcularSalario salario = salario + (salario * 0.05) - (salario * 0.07)