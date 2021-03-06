// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2020, Intel Corporation */

/*
 * conn_cfg-sq_size.c -- the rpma_conn_cfg_set/get_sq_size() unit tests
 *
 * APIs covered:
 * - rpma_conn_cfg_set_sq_size()
 * - rpma_conn_cfg_get_sq_size()
 */

#include "conn_cfg-common.h"
#include "test-common.h"

/*
 * set__cfg_NULL -- NULL cfg is invalid
 */
static void
set__cfg_NULL(void **unused)
{
	/* run test */
	int ret = rpma_conn_cfg_set_sq_size(NULL, MOCK_Q_SIZE);

	/* verify the results */
	assert_int_equal(ret, RPMA_E_INVAL);
}

/*
 * get__cfg_NULL -- NULL cfg is invalid
 */
static void
get__cfg_NULL(void **unused)
{
	/* run test */
	uint32_t sq_size;
	int ret = rpma_conn_cfg_get_sq_size(NULL, &sq_size);

	/* verify the results */
	assert_int_equal(ret, RPMA_E_INVAL);
}

/*
 * get__sq_size_NULL -- NULL sq_size is invalid
 */
static void
get__sq_size_NULL(void **cstate_ptr)
{
	struct conn_cfg_test_state *cstate = *cstate_ptr;

	/* run test */
	int ret = rpma_conn_cfg_get_sq_size(cstate->cfg, NULL);

	/* verify the results */
	assert_int_equal(ret, RPMA_E_INVAL);
}

/*
 * sq_size__lifecycle -- happy day scenario
 */
static void
sq_size__lifecycle(void **cstate_ptr)
{
	struct conn_cfg_test_state *cstate = *cstate_ptr;

	/* run test */
	int ret = rpma_conn_cfg_set_sq_size(cstate->cfg, MOCK_Q_SIZE);

	/* verify the results */
	assert_int_equal(ret, MOCK_OK);
	uint32_t sq_size;
	ret = rpma_conn_cfg_get_sq_size(cstate->cfg, &sq_size);
	assert_int_equal(ret, MOCK_OK);
	assert_int_equal(sq_size, MOCK_Q_SIZE);
}


static const struct CMUnitTest test_sq_size[] = {
	/* rpma_conn_cfg_set_sq_size() unit tests */
	cmocka_unit_test(set__cfg_NULL),

	/* rpma_conn_cfg_get_sq_size() unit tests */
	cmocka_unit_test(get__cfg_NULL),
	cmocka_unit_test_setup_teardown(get__sq_size_NULL,
		setup__conn_cfg, teardown__conn_cfg),

	/* rpma_conn_cfg_set/get_sq_size() lifecycle */
	cmocka_unit_test_setup_teardown(sq_size__lifecycle,
		setup__conn_cfg, teardown__conn_cfg),
};

int
main(int argc, char *argv[])
{
	return cmocka_run_group_tests(test_sq_size, NULL, NULL);
}
