#include "Unit.h"
#include <cstdint>
#include <vector>
#include <array>
#include <memory>
#include <algorithm>

namespace FD
{
    uint8_t GetCustomAreaSize(const std::vector<uint8_t> & data, std::vector<uint8_t>::const_iterator it)
    {
        // Find the start
        uint8_t length;
        uint8_t offset;
        bool found = false;
        uint8_t total_length = 0;
        std::vector<uint8_t>::const_iterator startIt = it;
        std::vector<uint8_t>::const_iterator endIt = it;

        for (auto iit = data.begin(); iit != data.end(); iit++)
        {
            if (iit == it)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            offset = it - data.begin();

            for (; it != data.end(); )
            {
                length = (*it & 0x3F);
                // +1 for move to next possible type length byte
                it += length + 1;
                // Padding or End of Field
                if ((*endIt == 0x00) || (*endIt == 0xC1))
                {
                    break;
                }
            }

            total_length = endIt - startIt;
        }

        return total_length;
    }

    bool FD::CommonHeader::SetData(const std::vector<uint8_t> & data)
    {
        if (data.size() != 8)
        {
            return false;
        }

        this->formatVersion = data[0];
        this->internalUse = data[1];
        this->chassisInfo = data[2];
        this->boardArea = data[3];
        this->productInfoArea = data[4];
        this->multiRecordArea = data[5];
        this->pad = data[6];
        this->checksum = data[7];

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::CommonHeader::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        vec.get()->push_back(this->formatVersion);
        vec.get()->push_back(this->internalUse);
        vec.get()->push_back(this->chassisInfo);
        vec.get()->push_back(this->boardArea);
        vec.get()->push_back(this->productInfoArea);
        vec.get()->push_back(this->multiRecordArea);
        vec.get()->push_back(this->pad);
        vec.get()->push_back(this->checksum);

        return vec;
    }

    bool FD::CommonHeader::CalculateChecksum() const
    {
        auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        return true;
    }

    bool FD::InternalUseArea::SetData(const std::vector<uint8_t> & data)
    {
        this->formatVersion = data[0];
        this->info = std::vector<uint8_t>(data.begin() + 1, data.end());
        return true;
    }

    bool FD::InternalUseArea::CalculateChecksum() const
    {
       auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::InternalUseArea::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        vec.get()->push_back(this->formatVersion);

        for (auto it = this->info.begin(); it != this->info.end(); it++)
        {
            vec.get()->push_back(*it);
        }

        return vec;
    }

    bool FD::ChassisInfoArea::SetData(const std::vector<uint8_t> & data)
    {
        uint8_t length = 0;
        uint8_t offset = 0;
        this->formatVersion = data[0];
        this->length = data[1];
        this->type = data[2];

        offset = 3;
        this->partNumberTL = data[offset];
        length = (this->partNumberTL & 0x3F);
        offset++; // start from actual data
        this->partNumber = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        this->serialNumberTL = data[offset];
        length = (this->serialNumberTL & 0x3F);
        offset++; // start from actual data
        this->serialNumber = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        length = GetCustomAreaSize(data, data.begin() + offset);
        this->customFields = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        length = ((this->length * 8) - offset) - 1; // Space between checksum and custom area

        this->checksum = *(data.end() - 1);

        return true;
    }

    bool FD::ChassisInfoArea::CalculateChecksum() const
    {
       auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        this->checksum = 0x100 - cs;

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::ChassisInfoArea::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        return vec;
    }

    bool FD::BoardArea::SetData(const std::vector<uint8_t> & data)
    {
        uint8_t length = 0;
        uint8_t offset = 0;
        this->formatVersion = data[0];
        this->length = data[1];
        this->languageCode = data[2];
        offset = 3;
        length = 3;
        this->manufacturerDateTime = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        this->manufacturerNameTL = data[offset];
        length = (this->manufacturerNameTL & 0x3F);
        offset++; // start from actual data
        this->manufacturerName = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        this->productNameTL = data[offset];
        length = (this->productNameTL & 0x3F);
        offset++; // start from actual data
        this->productName = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        this->serialNumberTL = data[offset];
        length = (this->serialNumberTL & 0x3F);
        offset++; // start from actual data
        this->serialNumber = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        this->partNumberTL = data[offset];
        length = (this->partNumberTL & 0x3F);
        offset++; // start from actual data
        this->partNumber = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        this->fruFileIDTL = data[offset];
        length = (this->fruFileIDTL & 0x3F);
        offset++; // start from actual data
        this->fruFileID = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        offset += length;
        length = GetCustomAreaSize(data, data.begin() + offset);
        this->customFields = std::vector<uint8_t>(data.begin() + offset, data.begin() + offset + length);

        length = ((this->length * 8) - offset) - 1; // Space between checksum and custom area
        offset += length;

        this->checksum = data[offset];

        return true;
    }

    bool FD::BoardArea::CalculateChecksum() const
    {
        auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        this->checksum = 0x100 - cs;

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::BoardArea::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        return vec;
    }

    bool FD::ProductInfoArea::SetData(const std::vector<uint8_t> & data)
    {
        return false;
    }

    bool FD::ProductInfoArea::CalculateChecksum() const
    {
       auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        this->checksum = 0x100 - cs;

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::ProductInfoArea::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        return vec;
    }

    bool FD::MultiRecordArea::SetData(const std::vector<uint8_t> & data)
    {
        return false;
    }

    bool FD::MultiRecordArea::CalculateChecksum() const
    {
       auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        // this->checksum = 0x100 - cs;

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::MultiRecordArea::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        return vec;
    }

    bool FD::Unit::SetData(const std::vector<uint8_t> & data)
    {
        std::vector<uint8_t> hv = std::vector<uint8_t>(data.begin(), data.begin() + 8);
        if (!header.SetData(const_cast<std::vector<uint8_t>&>(hv)))
        {
            return false;
        }

        if (header.internalUse != 0)
        {
            std::vector<uint8_t> iuav = std::vector<uint8_t>(data.begin() + (header.internalUse * 8), data.end());
            chassisInfoArea.SetData(const_cast<std::vector<uint8_t>&>(iuav));
        }

        if (header.chassisInfo != 0)
        {
            std::vector<uint8_t> ciav = std::vector<uint8_t>(data.begin() + (header.chassisInfo * 8), data.end());
            chassisInfoArea.SetData(const_cast<std::vector<uint8_t>&>(ciav));
        }

        if (header.boardArea != 0)
        {
            std::vector<uint8_t> bav = std::vector<uint8_t>(data.begin() + (header.boardArea * 8), data.end());
            boardArea.SetData(const_cast<std::vector<uint8_t>&>(bav));
        }

        if (header.productInfoArea != 0)
        {
            std::vector<uint8_t> piav = std::vector<uint8_t>(data.begin() + (header.productInfoArea * 8), data.end());
            boardArea.SetData(const_cast<std::vector<uint8_t>&>(piav));
        }

        if (header.multiRecordArea != 0)
        {
            std::vector<uint8_t> mrav = std::vector<uint8_t>(data.begin() + (header.multiRecordArea * 8), data.end());
            //multiRecordArea.SetData(const_cast<std::vector<uint8_t>&>(mrav));
        }

        return true;
    }

    bool FD::Unit::CalculateChecksum() const
    {
       auto data = this->GetData();
        size_t cs = 0;

        for (auto it = data->begin(); it != data->end(); it++)
        {
            cs += *it;
        }

        return true;
    }

    std::unique_ptr<std::vector<uint8_t>> FD::Unit::GetData() const
    {
        std::unique_ptr<std::vector<uint8_t>> vec = std::make_unique<std::vector<uint8_t>>();
        return vec;
    }
}
