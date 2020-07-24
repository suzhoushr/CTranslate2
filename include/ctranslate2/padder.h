#pragma once

#include "ops/gather.h"
#include "storage_view.h"

namespace ctranslate2 {

  // This class can be used to dynamically remove or add padding.
  // This is useful to save on computation when lengths are very different.
  class Padder {
  public:
    // If max_time is negative, it is set to the maximum length.
    Padder(const StorageView& lengths, const dim_t max_time = -1);

    // Merge batch and time dimensions and remove padding.
    void remove_padding(StorageView& x) const;

    // Split first dimension into batch and time dimensions and add padding.
    void add_padding(StorageView& x) const;

  private:
    dim_t _batch_size;
    dim_t _max_time;
    StorageView _padding_to_flat;
    StorageView _flat_to_padding;
    const ops::Gather _gather_op;
  };

}