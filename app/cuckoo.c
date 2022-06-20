#include <app/cuckoo.h>
#include <app/app.h>
#include <stdlib.h>

// Shared Variables
 __nv cuckoo_fingerprint_t   _v_filter[CUCKOO_NUM_BUCKETS];
 __nv cuckoo_index_t         _v_index;
 __nv cuckoo_value_t         _v_key;
 __nv TaskName               _v_next_task;
 __nv cuckoo_fingerprint_t   _v_fingerprint;
 __nv cuckoo_value_t         _v_index1;
 __nv cuckoo_value_t         _v_index2;
 __nv cuckoo_value_t         _v_relocation_count;
 __nv cuckoo_value_t         _v_insert_count;
 __nv cuckoo_value_t         _v_inserted_count;
 __nv cuckoo_value_t         _v_lookup_count;
 __nv cuckoo_value_t         _v_member_count;
 __nv uint16_t               _v_success;
 __nv uint16_t               _v_member;


 cuckoo_hash_t CUCKOO_DjbHash(uint8_t* data, uint16_t len);
 cuckoo_index_t CUCKOO_Hash2Index(cuckoo_fingerprint_t fp);
 cuckoo_fingerprint_t CUCKOO_Hash2Fingerprint(cuckoo_value_t key);


void CUCKOO_main()
{
    uint16_t i;
    cuckoo_index_t fp_hash;
    uint16_t __cry;
    uint16_t __cry_idx;
    uint16_t __cry_idx2;
    cuckoo_fingerprint_t fp_victim;
    cuckoo_index_t fp_hash_victim;
    cuckoo_index_t index2_victim;

    for (i = 0; i < CUCKOO_NUM_BUCKETS; ++i)
        _v_filter[i] = 0;

    _v_insert_count = 0;
    _v_lookup_count = 0;
    _v_inserted_count = 0;
    _v_member_count = 0;
    _v_key = cuckoo_init_key;
    _v_next_task = CUCKOO_Insert;

    // ---------------------------------------------------------
    KeyGenerate:
    _v_key = (_v_key + 1) * 17;
    if (_v_next_task == CUCKOO_Insert)
        goto Insert;
    else if (_v_next_task == CUCKOO_Lookup)
        goto Lookup;

    // ---------------------------------------------------------
    shared_calc_index:
    _v_fingerprint = CUCKOO_Hash2Fingerprint(_v_key);

    _v_index1 = CUCKOO_Hash2Index(_v_key);

    fp_hash = CUCKOO_Hash2Index(_v_fingerprint);
    _v_index2 = _v_index1 ^ fp_hash;

    if (_v_next_task == CUCKOO_Add)
        goto Add;
    else if (_v_next_task == CUCKOO_Lookup_Search)
        goto Lookup_Search;

    // ---------------------------------------------------------
    Insert:
    _v_next_task = CUCKOO_Add;
    goto shared_calc_index;

    // ---------------------------------------------------------
    Lookup:
    _v_next_task = CUCKOO_Lookup_Search;
    goto shared_calc_index;

    // ---------------------------------------------------------
    Add:
    __cry_idx = _v_index1;
    __cry_idx2 = _v_index2;

    if (!_v_filter[__cry_idx])
    {
        _v_success = 1;
        _v_filter[__cry_idx] = _v_fingerprint;
        goto Insert_Done;
    }
    else
    {
        if (!_v_filter[__cry_idx2])
        {
            _v_success = 1;
            _v_filter[__cry_idx2] = _v_fingerprint;
            goto Insert_Done;
        }
        else
        {
            cuckoo_fingerprint_t fp_victim;
            cuckoo_index_t index_victim;
            if (rand() % 2)
            {
                index_victim = __cry_idx;
                fp_victim = _v_filter[__cry_idx];
            }
            else
            {
                index_victim = __cry_idx2;
                fp_victim = _v_filter[__cry_idx2];
            }
            _v_filter[index_victim] = _v_fingerprint;
            _v_index1 = index_victim;
            _v_fingerprint = fp_victim;
            _v_relocation_count = 0;
        }
    }

    Relocate:
    fp_victim = _v_fingerprint;
    fp_hash_victim = CUCKOO_Hash2Index(fp_victim);
    index2_victim = _v_index1 ^ fp_hash_victim;

    if (!_v_filter[index2_victim])
    {
        _v_success = 1;
        _v_filter[index2_victim] = fp_victim;
        goto Insert_Done;
    }
    else
    {
        if (_v_relocation_count >= CUCKOO_MAX_RELOCATIONS)
        {
            _v_success = 0;
            goto Insert_Done;
        }

        _v_relocation_count++;
        _v_index1 = index2_victim;
        _v_fingerprint = _v_filter[index2_victim];
        _v_filter[index2_victim] = fp_victim;
        goto Relocate;
    }

    Insert_Done:
    _v_insert_count++;
    __cry = _v_inserted_count;
    __cry += _v_success;
    _v_inserted_count = __cry;

    if (_v_insert_count < CUCKOO_NUM_INSERTS)
    {
        _v_next_task = CUCKOO_Insert;
        goto KeyGenerate;
    }
    else
    {
        _v_next_task = CUCKOO_Lookup;
        _v_key = cuckoo_init_key;
        goto KeyGenerate;
    }

    // ---------------------------------------------------------
    Lookup_Search:

    if (_v_filter[_v_index1] == _v_fingerprint)
        _v_member = 1;
    else if (_v_filter[_v_index2] == _v_fingerprint)
        _v_member = 1;
    else
        _v_member = 0;

    _v_lookup_count++;
    __cry = _v_member_count;
    __cry += _v_member;
    _v_member_count = __cry;

    if (_v_lookup_count < CUCKOO_NUM_LOOKUPS)
    {
        _v_next_task = CUCKOO_Lookup;
        goto KeyGenerate;
    }
    else
    {
        goto final;
    }

    final:
    return;

}

cuckoo_hash_t CUCKOO_DjbHash(uint8_t* data, uint16_t len)
{
    uint16_t hash = 5381;
    uint16_t i;

    for (i = 0; i < len; data++, i++)
        hash = ((hash << 5) + hash) + (*data);

    return hash & 0xFFFF;
}

cuckoo_index_t CUCKOO_Hash2Index(cuckoo_fingerprint_t fp)
{
    cuckoo_hash_t hash = CUCKOO_DjbHash((uint8_t *) &fp, sizeof(cuckoo_fingerprint_t));
    return hash & (CUCKOO_NUM_BUCKETS - 1); // NUM_BUCKETS must be power of 2
}

cuckoo_fingerprint_t CUCKOO_Hash2Fingerprint(cuckoo_value_t key)
{
    return CUCKOO_DjbHash((uint8_t *) &key, sizeof(cuckoo_value_t));
}
