/* Copyright (C) 2021 Alexander Procelewski - All Rights Reserved
 * https://github.com/alexthe2/CLinkedList
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 */

#ifndef LIST_TOOLS_H_
#define LIST_TOOLS_H_

#include <string.h>
#include "Utils.h"

#pragma region Compare Functions
int CompareFunctionInt(void* a, void* b);
#define INT_LIST_CMP CompareFunctionInt

int CompareFunctionDouble(void* a, void* b);
#define DOUBLE_LIST_CMP CompareFunctionDouble

int CompareFunctionFloat(void* a, void* b);
#define FLOAT_LIST_CMP CompareFunctionFloat

int CompareFunctionString(void* a, void* b);
#define STRING_LIST_CMP CompareFunctionString

#pragma endregion

#pragma region Packers
/// <summary>
/// Packs an Int so that it can be added to the list
/// </summary>
/// <param name="content"></param>
/// <returns></returns>
void* PackInt(int content);

/// <summary>
/// Packs a double so that it can be added to the list
/// </summary>
/// <param name="content"></param>
/// <returns></returns>
void* PackDouble(double content);

/// <summary>
/// Packs a float so that it can be added to the list
/// </summary>
/// <param name="content"></param>
/// <returns></returns>
void* PackFloat(float content);

/// <summary>
/// Packs a string so that it can be added to the list
/// </summary>
/// <param name="content"></param>
/// <returns></returns>
void* PackString(const char* content);
#pragma endregion

/// <summary>
/// A very basic free function for the list
/// </summary>
/// <param name="ctx"></param>
void EasyFree(void* ctx);

#endif // LIST_TOOLS_H_
