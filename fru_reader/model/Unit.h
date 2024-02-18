#pragma once
#include <memory>
#include <vector>
#include <cstdint>

namespace FD
{
    class IFRUInfoArea
    {
        virtual bool SetData(const std::vector<uint8_t> & data) = 0;
        virtual std::unique_ptr<std::vector<uint8_t>> GetData() const = 0;
        virtual bool CalculateChecksum() const = 0;
    };

    struct CommonHeader : IFRUInfoArea
    {
        uint8_t formatVersion = 0;
        uint8_t internalUse = 0;
        uint8_t chassisInfo = 0;
        uint8_t boardArea = 0;
        uint8_t boardAreaLength = 0;
        uint8_t productInfoArea = 0;
        uint8_t multiRecordArea = 0;
        uint8_t pad = 0;
        mutable uint8_t checksum = 0;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };

    struct InternalUseArea : IFRUInfoArea
    {
        uint8_t formatVersion = 0;
        std::vector<uint8_t> info;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };

    struct ChassisInfoArea : IFRUInfoArea
    {
        uint8_t formatVersion = 0;
        uint8_t length = 0;
        uint8_t type = 0;
        uint8_t partNumberTL = 0;
        std::vector<uint8_t> partNumber;
        uint8_t serialNumberTL = 0;
        std::vector<uint8_t> serialNumber;
        std::vector<uint8_t> customFields;
        uint8_t end = 0;
        std::vector<uint8_t> padding;
        mutable uint8_t checksum = 0;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };

    struct BoardArea : IFRUInfoArea
    {
        uint8_t formatVersion = 0;
        uint8_t length = 0;
        uint8_t languageCode = 0;
        std::vector<uint8_t> manufacturerDateTime;
        uint8_t manufacturerNameTL = 0;
        std::vector<uint8_t> manufacturerName;
        uint8_t productNameTL = 0;
        std::vector<uint8_t> productName;
        uint8_t serialNumberTL = 0;
        std::vector<uint8_t> serialNumber;
        uint8_t partNumberTL = 0;
        std::vector<uint8_t> partNumber;
        uint8_t fruFileIDTL = 0;
        std::vector<uint8_t> fruFileID;
        std::vector<uint8_t> customFields;
        uint8_t end = 0;
        std::vector<uint8_t> padding;
        mutable uint8_t checksum = 0;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };

    struct ProductInfoArea : IFRUInfoArea
    {
        uint8_t formatVersion = 0;
        uint8_t length = 0;
        uint8_t languageCode = 0;
        uint8_t manufacturerNameTL = 0;
        std::vector<uint8_t> manufacturerName;
        uint8_t productNameTL = 0;
        std::vector<uint8_t> productName;
        uint8_t partNumberTL = 0;
        std::vector<uint8_t> partNumber;
        uint8_t productVersionTL = 0;
        std::vector<uint8_t> productVersion;
        uint8_t serialNumberTL = 0;
        std::vector<uint8_t> serialNumber;
        uint8_t assetTagTL = 0;
        std::vector<uint8_t> assetTag;
        uint8_t fruFileIDTL = 0;
        std::vector<uint8_t> fruFileID;
        std::vector<uint8_t> customFields;
        uint8_t end = 0;
        std::vector<uint8_t> padding;
        mutable uint8_t checksum = 0;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };

    struct MultiRecordAreaHeader
    {
        uint8_t recordTypeID = 0;
        uint8_t formatVersionEnd = 0;
        uint8_t length = 0;
        mutable uint8_t checksumRecord = 0;
        mutable uint8_t checksumHeader = 0;
    };

    struct MultiRecordArea : IFRUInfoArea
    {
        MultiRecordAreaHeader header;
        std::vector<uint8_t> data;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };

    struct Unit : IFRUInfoArea
    {
        bool isEdited;
        CommonHeader header;
        InternalUseArea internalUseArea;
        ChassisInfoArea chassisInfoArea;
        BoardArea boardArea;
        ProductInfoArea productInfoArea;
        std::vector<MultiRecordArea> multiRecordArea;

        bool SetData(const std::vector<uint8_t> & data);
        std::unique_ptr<std::vector<uint8_t>> GetData() const;
        bool CalculateChecksum() const;
    };
}
