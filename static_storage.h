#pragma once

bool StaticStorage_Init(const char *defaultPayload);
bool StaticStorage_Write(const char *payLoad);
const char *StaticStorage_Read();
