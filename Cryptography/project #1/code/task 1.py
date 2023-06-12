def decrypt(__ciphertext: str):
    # greek alphabet shifted back by 3
    caesar_cipher = {
        'α': 'χ', 'β': 'ψ', 'γ': 'ω', 'δ': 'α', 'ε': 'β', 'ζ': 'γ',
        'η': 'δ', 'θ': 'ε', 'ι': 'ζ', 'κ': 'η', 'λ': 'θ', 'μ': 'ι',
        'ν': 'κ', 'ξ': 'λ', 'ο': 'μ', 'π': 'ν', 'ρ': 'ξ', 'σ': 'ο',
        'τ': 'π', 'υ': 'ρ', 'φ': 'σ', 'χ': 'τ', 'ψ': 'υ', 'ω': 'φ',
    }
    # decrypt
    plaintext = ""
    for letter in __ciphertext:
        plaintext += caesar_cipher.get(letter)

    print(plaintext)


if __name__ == '__main__':
    decrypt("οκηθμφδζθγοθχυκχσφθμφμχγ")
