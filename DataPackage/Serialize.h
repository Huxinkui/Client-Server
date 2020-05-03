#ifndef _SERIALIZE_H
#define _SERIALIZE_H


//序列化
int Serialize(const DataPackage &s, char output[])
{
	int count = 0;
	memcpy(output, &s.age, sizeof(s.age));
	count += sizeof(s.age);
	memcpy(output + count , &s.name_size, sizeof(s.name_size));
	count += sizeof(s.name_size);
	memcpy(output  + count , &s.Gender_size, sizeof(s.Gender_size));
	count += sizeof(s.Gender_size);
	memcpy(output + count, s.name.c_str(), s.name.length());
	count += s.name.length();
	memcpy(output + count, s.Gender.c_str(), s.Gender.length());
	count += s.Gender.length();

	return count;
}
 
//反序列化
int Deserialize(DataPackage &s, const char *input, int count)
{
	int offset = 0;
	memcpy(&s.age, input, sizeof(s.age));
	offset += sizeof(s.age);
	memcpy(&s.name_size, input + offset , sizeof(s.name_size));
	offset += sizeof(s.name_size);
	memcpy(&s.Gender_size, input + offset,sizeof(s.Gender_size));
	offset += sizeof(s.Gender_size);
	s.name.append(input + offset, s.name_size);
	offset += s.name_size;

 	s.Gender.append(input + offset, s.Gender_size);
	offset  += s.Gender_size;

	return 0;
}


#endif