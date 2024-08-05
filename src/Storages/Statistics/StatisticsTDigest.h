#pragma once

#include <Storages/Statistics/Statistics.h>
#include <AggregateFunctions/QuantileTDigest.h>
#include <DataTypes/IDataType.h>

namespace DB
{

class StatisticsTDigest : public IStatistics
{
public:
    explicit StatisticsTDigest(const SingleStatisticsDescription & statistics_description, DataTypePtr data_type_);

    void update(const ColumnPtr & column) override;

    void serialize(WriteBuffer & buf) override;
    void deserialize(ReadBuffer & buf) override;

    Float64 estimateLess(const Field & val) const override;
    Float64 estimateEqual(const Field & val) const override;

private:
    QuantileTDigest<Float64> t_digest;
    DataTypePtr data_type;
};

void tdigestStatisticsValidator(const SingleStatisticsDescription & statistics_description, DataTypePtr data_type);
StatisticsPtr tdigestStatisticsCreator(const SingleStatisticsDescription & statistics_description, DataTypePtr);

}
