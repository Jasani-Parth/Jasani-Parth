def KaratSuba_Multiplication(x, y):

    """
    - Karatsuba's Algorithm Is Based On Divide And Conqure Method.

    - We Can Write ...
        x = a * 10^(n/2) + b
        y = c * 10^(n/2) + d

    - x * y = (ac)*(10^(n)) + (ad+bc)*(10^(n/2)) + bd
            = (ac)*(10^(n)) + ((a+b)*(c+d) - ac - bd)*(10^(n/2)) + bd

    - Recurrance Relation
        T(n) = 3 * T(n/2) + O(n)

    - Time-Complexicity : O(n^(log2 (3))) = O(n^1.58)

    - Brute-Force Time-Complexicity : O(n^2)
    """

    if x < 10 or y < 10:
        return x * y
    else:

        l = len(str(x))
        p10 = 10 ** (l // 2)

        a = x // p10
        b = x % p10
        c = y // p10
        d = y % p10

        ac = KaratSuba_Multiplication(a, c)
        bd = KaratSuba_Multiplication(b, d)
        abcd = KaratSuba_Multiplication(a + b, c + d)

        return ac * (p10 ** 2) + (abcd - ac - bd) * p10 + bd


def make_equal(x, y):

    x = str(x)
    y = str(y)

    if len(x) < len(y):

        while len(x) < len(y):
            x = "0" + x

    elif len(x) > len(y):

        while len(x) > len(y):
            y = "0" + y

    return [int(x), int(y)]


if __name__ == "__main__":

    print(KaratSuba_Multiplication.__doc__)

    X = int(input("Enter X : "))
    Y = int(input("Enter Y : "))

    X, Y = make_equal(X, Y)

    print(KaratSuba_Multiplication(X, Y))
