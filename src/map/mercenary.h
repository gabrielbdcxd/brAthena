/****************************************************************************!
*                _           _   _   _                                       *
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *
*                                                                            *
******************************************************************************
*                          www.brathena.org                                  *
*****************************************************************************/

#ifndef MAP_MERCENARY_H
#define MAP_MERCENARY_H

#include "status.h" // struct status_data, struct status_change
#include "unit.h" // struct unit_data
#include "../common/cbasetypes.h"

// number of cells that a mercenary can walk to from it's master before being warped
#define MAX_MER_DISTANCE 15

enum {
	ARCH_MERC_GUILD,
	SPEAR_MERC_GUILD,
	SWORD_MERC_GUILD,
};

struct s_mercenary_db {
	int class_;
	char sprite[NAME_LENGTH], name[NAME_LENGTH];
	unsigned short lv;
	short range2, range3;
	struct status_data status;
	struct view_data vd;
	struct {
		unsigned short id, lv;
	} skill[MAX_MERCSKILL];
};

struct mercenary_data {
	struct block_list bl;
	struct unit_data ud;
	struct view_data *vd;
	struct status_data base_status, battle_status;
	struct status_change sc;
	struct regen_data regen;
	struct s_mercenary_db *db;
	struct s_mercenary mercenary;
	char blockskill[MAX_SKILL];

	struct map_session_data *master;
	int contract_timer;

	unsigned devotion_flag : 1;
	int64 masterteleport_timer;
};

/*=====================================
* Interface : mercenary.h
* Generated by HerculesInterfaceMaker
* created by Susu
*-------------------------------------*/
struct mercenary_interface {

	/* vars */

	struct s_mercenary_db db[MAX_MERCENARY_CLASS];

	/* funcs */

	void (*init) (bool minimal);

	bool (*class) (int class_);
	struct view_data * (*get_viewdata) (int class_);

	int (*create) (struct map_session_data *sd, int class_, unsigned int lifetime);
	int (*data_received) (struct s_mercenary *merc, bool flag);
	int (*save) (struct mercenary_data *md);

	void (*heal) (struct mercenary_data *md, int hp, int sp);
	int (*dead) (struct mercenary_data *md);

	int (*delete) (struct mercenary_data *md, int reply);
	void (*contract_stop) (struct mercenary_data *md);

	int (*get_lifetime) (struct mercenary_data *md);
	int (*get_guild) (struct mercenary_data *md);
	int (*get_faith) (struct mercenary_data *md);
	int (*set_faith) (struct mercenary_data *md, int value);
	int (*get_calls) (struct mercenary_data *md);
	int (*set_calls) (struct mercenary_data *md, int value);
	int (*kills) (struct mercenary_data *md);

	int (*checkskill) (struct mercenary_data *md, uint16 skill_id);
	int (*read_db) (void);
	int (*read_skilldb) (void);

	int (*killbonus) (struct mercenary_data *md);
	int (*search_index) (int class_);

	int (*contract_end_timer) (int tid, int64 tick, int id, intptr_t data);
	bool (*read_db_sub) (char* str[], int columns, int current);
	bool (*read_skill_db_sub) (char* str[], int columns, int current);
};

struct mercenary_interface *mercenary;

#ifdef BRATHENA_CORE
void mercenary_defaults(void);
#endif // BRATHENA_CORE

#endif /* MAP_MERCENARY_H */
