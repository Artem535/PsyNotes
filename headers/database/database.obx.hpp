// Code generated by ObjectBox; DO NOT EDIT.

#pragma once

#include <cstdbool>
#include <cstdint>

#include "flatbuffers/flatbuffers.h"
#include "objectbox.h"
#include "objectbox.hpp"

struct NoteText; 

struct Note_;

struct Note {
    obx_id id;
    uint64_t time;
    obx_id noteTextId;
    int8_t emotState;
    std::string title;
    int8_t angryLevel;
    int8_t sadLevel;
    int8_t loveLevel;
    int8_t fearLevel;
    int8_t happyLevel;
    bool visible;

    struct _OBX_MetaInfo {
        static constexpr obx_schema_id entityId() { return 1; }
    
        static void setObjectId(Note& object, obx_id newId) { object.id = newId; }
    
        /// Write given object to the FlatBufferBuilder
        static void toFlatBuffer(flatbuffers::FlatBufferBuilder& fbb, const Note& object);
    
        /// Read an object from a valid FlatBuffer
        static Note fromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static std::unique_ptr<Note> newFromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static void fromFlatBuffer(const void* data, size_t size, Note& outObject);
    };
};

struct Note_ {
    static const obx::Property<Note, OBXPropertyType_Long> id;
    static const obx::Property<Note, OBXPropertyType_Date> time;
    static const obx::RelationProperty<Note, NoteText> noteTextId;
    static const obx::Property<Note, OBXPropertyType_Byte> emotState;
    static const obx::Property<Note, OBXPropertyType_String> title;
    static const obx::Property<Note, OBXPropertyType_Byte> angryLevel;
    static const obx::Property<Note, OBXPropertyType_Byte> sadLevel;
    static const obx::Property<Note, OBXPropertyType_Byte> loveLevel;
    static const obx::Property<Note, OBXPropertyType_Byte> fearLevel;
    static const obx::Property<Note, OBXPropertyType_Byte> happyLevel;
    static const obx::Property<Note, OBXPropertyType_Bool> visible;
};


struct NoteText_;

struct NoteText {
    obx_id id;
    std::string thoughtsTxt;
    std::string behaviorTxt;
    std::string bodyTxt;
    std::string feelsTxt;
    std::string situationTxt;

    struct _OBX_MetaInfo {
        static constexpr obx_schema_id entityId() { return 3; }
    
        static void setObjectId(NoteText& object, obx_id newId) { object.id = newId; }
    
        /// Write given object to the FlatBufferBuilder
        static void toFlatBuffer(flatbuffers::FlatBufferBuilder& fbb, const NoteText& object);
    
        /// Read an object from a valid FlatBuffer
        static NoteText fromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static std::unique_ptr<NoteText> newFromFlatBuffer(const void* data, size_t size);
    
        /// Read an object from a valid FlatBuffer
        static void fromFlatBuffer(const void* data, size_t size, NoteText& outObject);
    };
};

struct NoteText_ {
    static const obx::Property<NoteText, OBXPropertyType_Long> id;
    static const obx::Property<NoteText, OBXPropertyType_String> thoughtsTxt;
    static const obx::Property<NoteText, OBXPropertyType_String> behaviorTxt;
    static const obx::Property<NoteText, OBXPropertyType_String> bodyTxt;
    static const obx::Property<NoteText, OBXPropertyType_String> feelsTxt;
    static const obx::Property<NoteText, OBXPropertyType_String> situationTxt;
};

