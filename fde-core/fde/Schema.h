//
// Created by mvonkeil on 22.11.22.
//

#ifndef FDE_SCHEMA_H
#define FDE_SCHEMA_H

#include <map>
#include <string>

namespace fde {

class SchemaField {
};

class StringSchemaField : public SchemaField {
public:
    using field_type = std::string;
};

class Schema {
private:
    std::map<std::string, SchemaField> _fields;
};

}// namespace fde

#endif//FDE_SCHEMA_H
