#ifndef DAWGDIC_DAWG_H
#define DAWGDIC_DAWG_H

#include "base-types.h"
#include "object-pool.h"

#include <iostream>

namespace dawgdic {

class Dawg
{
public:
	Dawg() : base_pool_(), label_pool_(), flag_pool_(), num_of_states_(0),
		num_of_merged_states_(0), num_of_merging_states_(0) {}

	// The root index.
	BaseType root() const { return 0; }

	// Number of fixed transitions.
	SizeType size() const { return base_pool_.size(); }
	SizeType num_of_transitions() const { return base_pool_.size(); }
	// Number of states.
	SizeType num_of_states() const { return num_of_states_; }
	// Number of merged states.
	SizeType num_of_merged_states() const { return num_of_merged_states_; }
	// Number of merging states.
	SizeType num_of_merging_states() const { return num_of_merging_states_; }

	// Reads values.
	BaseType child(BaseType index) const
	{ return base_pool_[index] >> 2; }
	BaseType sibling(BaseType index) const
	{ return (base_pool_[index] & 1) ? (index + 1) : 0; }
	ValueType value(BaseType index) const
	{ return static_cast<ValueType>(base_pool_[index] >> 1); }
	bool is_leaf(BaseType index) const
	{ return label(index) == '\0'; }
	UCharType label(BaseType index) const
	{ return label_pool_[index]; }
	bool is_merging(BaseType index) const
	{ return (flag_pool_[index / 8] & (1 << (index % 8))) ? true : false; }

	// Clears object pools.
	void Clear()
	{
		base_pool_.Clear();
		label_pool_.Clear();
		flag_pool_.Clear();
		num_of_states_ = 0;
		num_of_merged_states_ = 0;
	}

public:
	// Following member functions are called from DawgBuilder.

	// Sets the number of states.
	void set_num_of_states(SizeType num_of_states)
	{
		num_of_states_ = num_of_states;
	}
	// Sets the number of merged states.
	void set_num_of_merged_states(SizeType num_of_merged_states)
	{
		num_of_merged_states_ = num_of_merged_states;
	}
	// Sets the number of merging states.
	void set_num_of_merging_states(SizeType num_of_merging_states)
	{
		num_of_merging_states_ = num_of_merging_states;
	}

	// Swaps base pools.
	void SwapBasePool(ObjectPool<BaseType> *base_pool)
	{
		base_pool_.Swap(base_pool);
	}
	// Swaps label pools.
	void SwapLabelPool(ObjectPool<UCharType> *label_pool)
	{
		label_pool_.Swap(label_pool);
	}
	// Swaps flag pools.
	void SwapFlagPool(ObjectPool<UCharType> *flag_pool)
	{
		flag_pool_.Swap(flag_pool);
	}

private:
	ObjectPool<BaseType> base_pool_;
	ObjectPool<UCharType> label_pool_;
	ObjectPool<UCharType> flag_pool_;
	SizeType num_of_states_;
	SizeType num_of_merged_states_;
	SizeType num_of_merging_states_;

	// Disallows copies.
	Dawg(const Dawg &);
	Dawg &operator=(const Dawg &);
};

}  // namespace dawgdic

#endif  // DAWGDIC_DAWG_H