module Strings where

-- Exercício 2

-- a) Uma função ehVazia :: String -> Bool que verifique se uma string é vazia.
ehVazia :: String -> Bool
ehVazia s = null s

-- b) Uma função ehLonga :: String -> Bool que verifique se uma string tem mais de 5 caracteres.
ehLonga :: String -> Bool
ehLonga s = checar 5 s
    where
        checar :: Int -> String -> Bool
        checar 0 (_:_) = True   
        checar 0 []    = False  
        checar _ []    = False  
        checar n (_:t) = checar (n - 1) t

-- c) Uma função ehCurta :: String -> Bool que verifique se uma string tem entre 1 e 5 caracteres (inclusive).
ehCurta :: String -> Bool
ehCurta "" = False
ehCurta s  = verificar 5 s
    where
        verificar :: Int -> String -> Bool
        verificar 0 (_:_) = False -- Tem mais de 5
        verificar 0 []    = True  -- Tem exatamente 5
        verificar _ []    = True  -- Tem entre 1 e 4
        verificar n (_:t) = verificar (n - 1) t

-- d) Uma função recursiva de alta ordem classificar :: [String] -> (String -> Bool) -> [String] que receba uma 
-- lista de strings e uma das funções acima, retornando apenas as strings que satisfazem a condição.
classificar :: [String] -> (String -> Bool) -> [String]
classificar [] _ = []
classificar (h:t) f
    | f h = h : classificar t f
    | otherwise = classificar t f