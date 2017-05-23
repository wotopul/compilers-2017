package org.wotopul

import org.wotopul.Primitive.*

fun strlen(str: StringT) = IntT(str.value.size)

fun strget(str: StringT, idx: IntT) = CharT(str.value[idx.value])

fun strset(str: StringT, idx: IntT, chr: CharT): IntT {
    str.value[idx.value] = chr.value
    return IntT(0)
}

fun strsub(str: StringT, offset: IntT, length: IntT): StringT {
    val substring = String(str.value, offset.value, length.value)
    return StringT(substring.toCharArray())
}

fun strdup(str: StringT) = StringT(str.value.copyOf())

fun strcat(str1: StringT, str2: StringT): StringT {
    val concatenated = String(str1.value) + String(str2.value)
    return StringT(concatenated.toCharArray())
}

fun strcmp(str1: StringT, str2: StringT): IntT {
    val res = String(str1.value).compareTo(String(str2.value))
    return IntT(res)
}

fun strmake(length: IntT, chr: CharT): StringT {
    val str = CharArray(length.value) { chr.value }
    return StringT(str)
}