#ifndef _SERIALIZE_H
#define _SERIALIZE_H


//序列化
// int Serialize(const DataPackage &s, char output[])
// {
// 	int count = 0;
// 	memcpy(output, &s.age, sizeof(s.age));
// 	count += sizeof(s.age);
// 	memcpy(output + count , &s.name_size, sizeof(s.name_size));
// 	count += sizeof(s.name_size);
// 	memcpy(output  + count , &s.Gender_size, sizeof(s.Gender_size));
// 	count += sizeof(s.Gender_size);
// 	memcpy(output + count, s.name.c_str(), s.name.length());
// 	count += s.name.length();
// 	memcpy(output + count, s.Gender.c_str(), s.Gender.length());
// 	count += s.Gender.length();

// 	return count;
// }
 
// //反序列化
// int Deserialize(DataPackage &s, const char *input, int count)
// {
// 	int offset = 0;
// 	memcpy(&s.age, input, sizeof(s.age));
// 	offset += sizeof(s.age);
// 	memcpy(&s.name_size, input + offset , sizeof(s.name_size));
// 	offset += sizeof(s.name_size);
// 	memcpy(&s.Gender_size, input + offset,sizeof(s.Gender_size));
// 	offset += sizeof(s.Gender_size);
// 	s.name.append(input + offset, s.name_size);
// 	offset += s.name_size;

//  s.Gender.append(input + offset, s.Gender_size);
// 	offset  += s.Gender_size;

// 	return 0;
// }
// 
int LoginSerialize(const Login &login, char output[])
{
	int count = 0;
	memcpy(output + count, &login.dataLenth, sizeof(login.dataLenth));
	count += sizeof(login.dataLenth);
	memcpy(output + count, &login.cmd, sizeof(login.cmd));
	count += sizeof(login.cmd);
	memcpy(output + count, &login.nameLength, sizeof(login.nameLength));
	count += sizeof(login.nameLength);
	memcpy(output + count, &login.passwordLength, sizeof(login.passwordLength));
	count += sizeof(login.passwordLength);
	memcpy(output + count, login.name.c_str(), login.name.length());
	count += login.name.length();
	//cout << " name size :" << login.name.length() << endl;
	memcpy(output + count, login.password.c_str(), login.password.length());
	count += login.password.length();
	return 0;
}
int LoginDeserialize(Login &login, const char *input, int count)
{
	int offset = 0;
	memcpy(&login.dataLenth, input, sizeof(login.dataLenth));
	offset += sizeof(login.dataLenth);
	memcpy(&login.cmd, input + offset, sizeof(login.cmd));
	offset += sizeof(login.cmd);
	memcpy(&login.nameLength, input + offset, sizeof(login.nameLength));
	offset += sizeof(login.nameLength);
	memcpy(&login.passwordLength, input + offset, sizeof(login.passwordLength));
	offset += sizeof(login.passwordLength);
	login.name.append(input + offset, login.nameLength);
	offset += login.nameLength;
	login.password.append(input + offset, login.passwordLength);
	//offset += login.passwordLength;
	return 0;
}

template<class INFO>
int InfoSerialize(const INFO &info, char output[] )
{
	int count = 0;
	memcpy(output + count, &info.dataLenth, sizeof(info.dataLenth));
	count += sizeof(info.dataLenth);
	memcpy(output + count, &info.cmd, sizeof(info.cmd));
	count += sizeof(info.cmd);
	memcpy(output + count, &info.infoLength, sizeof(info.infoLength));
	count += sizeof(info.infoLength);
	memcpy(output + count, info.info.c_str(), info.info.length());
	count += info.info.length();
	cout << "InfoSerialize: count :" << count << endl;
	return 0;
}

template<class INFO>
int InfoDeserialize(INFO &info, const char *input, int count)
{
	int offset = 0;
	memcpy(&info.dataLenth, input, sizeof(info.dataLenth));
	offset += sizeof(info.dataLenth);
	memcpy(&info.cmd, input + offset, sizeof(info.cmd));
	offset += sizeof(info.cmd);
	memcpy(&info.infoLength, input + offset, sizeof(info.infoLength));
	offset += sizeof(info.infoLength);
	info.info.append(input + offset, info.infoLength);
	return 0;
}
template<class DL>
int DLDeserialize(DL &info, const char *input, int count)
{
	int offset = 0;
	memcpy(&info.dataLenth, input, sizeof(info.dataLenth));
	offset += sizeof(info.dataLenth);
	memcpy(&info.cmd, input + offset, sizeof(info.cmd));
	return 0;
}
#endif