/*
 * Note: this file originally auto-generated by mib2c using
 *  : mib2c.table_data.conf,v 1.3 2004/10/14 12:57:34 dts12 Exp $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "disman/schedCore.h"
#include "disman/schedTable.h"
#include "utilities/iquery.h"

void  sched_nextTime( struct schedTable_entry *entry );
void  sched_nextRowTime( netsnmp_table_row *row );

/** Initializes the schedTable module */
void
init_schedTable(void)
{
    static oid      schedTable_oid[] = { 1, 3, 6, 1, 2, 1, 63, 1, 2 };
    size_t          schedTable_oid_len = OID_LENGTH(schedTable_oid);
    netsnmp_handler_registration *reg;
    extern netsnmp_table_data *schedTable;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("sched", "Initializing table\n"));
    reg =
        netsnmp_create_handler_registration("schedTable",
                                            schedTable_handler,
                                            schedTable_oid,
                                            schedTable_oid_len,
                                            HANDLER_CAN_RWRITE);

    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    netsnmp_table_helper_add_indexes(table_info, ASN_OCTET_STR, /* index: schedOwner */
                                     ASN_OCTET_STR,     /* index: schedName */
                                     0);
    table_info->min_column = COLUMN_SCHEDDESCR;
    table_info->max_column = COLUMN_SCHEDTRIGGERS;

    netsnmp_register_table_data(reg, schedTable, table_info);
}


/** handles requests for the schedTable table */
int
schedTable_handler(netsnmp_mib_handler *handler,
                   netsnmp_handler_registration *reginfo,
                   netsnmp_agent_request_info *reqinfo,
                   netsnmp_request_info *requests)
{

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    netsnmp_table_data *table_data;
    netsnmp_table_row *table_row;
    struct schedTable_entry *table_entry;
    int recalculate = 0;

    DEBUGMSGTL(("sched", "Handler (mode %d)\n", reqinfo->mode));
    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDDESCR:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedDescr,
                                         table_entry->schedDescr_len);
                break;
            case COLUMN_SCHEDINTERVAL:
                snmp_set_var_typed_value(request->requestvb, ASN_UNSIGNED,
                                         (u_char *)&table_entry->schedInterval,
                                         sizeof(table_entry->schedInterval));
                break;
            case COLUMN_SCHEDWEEKDAY:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)&table_entry->schedWeekDay,
                                         sizeof(table_entry->schedWeekDay));
                break;
            case COLUMN_SCHEDMONTH:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedMonth,
                                         sizeof(table_entry->schedMonth));
                break;
            case COLUMN_SCHEDDAY:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedDay,
                                         sizeof(table_entry->schedDay));
                break;
            case COLUMN_SCHEDHOUR:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedHour,
                                         sizeof(table_entry->schedHour));
                break;
            case COLUMN_SCHEDMINUTE:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedMinute,
                                         sizeof(table_entry->schedMinute));
                break;
            case COLUMN_SCHEDCONTEXTNAME:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedContextName,
                                         table_entry->schedContextName_len);
                break;
            case COLUMN_SCHEDVARIABLE:
                snmp_set_var_typed_value(request->requestvb, ASN_OBJECT_ID,
                                         (u_char *)table_entry->schedVariable,
                                         table_entry->schedVariable_len*sizeof(oid));
                break;
            case COLUMN_SCHEDVALUE:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedValue,
                                         sizeof(table_entry->schedValue));
                break;
            case COLUMN_SCHEDTYPE:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedType,
                                         sizeof(table_entry->schedType));
                break;
            case COLUMN_SCHEDADMINSTATUS:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedAdminStatus,
                                         sizeof(table_entry->schedAdminStatus));
                break;
            case COLUMN_SCHEDOPERSTATUS:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedOperStatus,
                                         sizeof(table_entry->schedOperStatus));
                break;
            case COLUMN_SCHEDFAILURES:
                snmp_set_var_typed_value(request->requestvb, ASN_COUNTER,
                                         (u_char *)&table_entry->schedFailures,
                                         sizeof(table_entry->schedFailures));
                break;
            case COLUMN_SCHEDLASTFAILURE:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedLastFailure,
                                         sizeof(table_entry->schedLastFailure));
                break;
#ifdef DTS_TOCHECK
            case COLUMN_SCHEDLASTFAILED:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *)table_entry->schedLastFailed,
                                         table_entry->schedLastFailed_len);
                break;
#endif
            case COLUMN_SCHEDSTORAGETYPE:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedStorageType,
                                         sizeof(table_entry->schedStorageType));
                break;
            case COLUMN_SCHEDROWSTATUS:
                snmp_set_var_typed_value(request->requestvb, ASN_INTEGER,
                                         (u_char *)&table_entry->schedRowStatus,
                                         sizeof(table_entry->schedRowStatus));
                break;
            case COLUMN_SCHEDTRIGGERS:
                snmp_set_var_typed_value(request->requestvb, ASN_COUNTER,
                                         (u_char *)&table_entry->schedTriggers,
                                         sizeof(table_entry->schedTriggers));
                break;
            }
        }
        break;

        /*
         * Write-support
         */
    case MODE_SET_RESERVE1:
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDDESCR:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 255) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDINTERVAL:
                if (request->requestvb->type != ASN_UNSIGNED) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len != sizeof(long)) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                /*
                 * Also may need to check value 
                 */
                break;
            case COLUMN_SCHEDWEEKDAY:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 1) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDMONTH:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 2) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDDAY:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 4+4) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDHOUR:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 3) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDMINUTE:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 8) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDCONTEXTNAME:
                if (request->requestvb->type != ASN_OCTET_STR) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > 32) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDVARIABLE:
                if (request->requestvb->type != ASN_OBJECT_ID) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len > MAX_OID_LEN) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                break;
            case COLUMN_SCHEDVALUE:
                if (request->requestvb->type != ASN_INTEGER) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len != sizeof(long)) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                /*
                 * Also may need to check value 
                 */
                break;
            case COLUMN_SCHEDTYPE:
                if (request->requestvb->type != ASN_INTEGER) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len != sizeof(long)) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                /*
                 * Also may need to check value 
                 */
                break;
            case COLUMN_SCHEDADMINSTATUS:
                if (request->requestvb->type != ASN_INTEGER) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len != sizeof(long)) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                /*
                 * Also may need to check value 
                 */
                break;
            case COLUMN_SCHEDSTORAGETYPE:
                if (request->requestvb->type != ASN_INTEGER) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len != sizeof(long)) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                /*
                 * Also may need to check value 
                 */
                break;
            case COLUMN_SCHEDROWSTATUS:
                if (request->requestvb->type != ASN_INTEGER) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGTYPE);
                    return SNMP_ERR_NOERROR;
                }
                if (request->requestvb->val_len != sizeof(long)) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGLENGTH);
                    return SNMP_ERR_NOERROR;
                }
                switch (*request->requestvb->val.integer) {
                case RS_ACTIVE:
                case RS_NOTINSERVICE:
                    if (!table_entry) {
                        netsnmp_set_request_error(reqinfo, request,
                                                  SNMP_ERR_INCONSISTENTVALUE);
                        return SNMP_ERR_NOERROR;
                    }
                    break;
                case RS_CREATEANDGO:
                case RS_CREATEANDWAIT:
                    if (table_entry) {
                        netsnmp_set_request_error(reqinfo, request,
                                                  SNMP_ERR_INCONSISTENTVALUE);
                        return SNMP_ERR_NOERROR;
                    }
                    break;
                case RS_DESTROY:
                    /*
                     * Valid in all circumstances 
                     */
                    break;
                case RS_NOTREADY:
                default:
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_ERR_WRONGVALUE);
                    return SNMP_ERR_NOERROR;
                    break;
                }
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_ERR_NOTWRITABLE);
                return SNMP_ERR_NOERROR;
            }
        }
        break;

    case MODE_SET_RESERVE2:
        for (request = requests; request; request = request->next) {
            table_row = (netsnmp_table_row *)
                netsnmp_extract_table_row(request);
            table_data = netsnmp_extract_table(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDROWSTATUS:
                switch (*request->requestvb->val.integer) {
                case RS_CREATEANDGO:
                case RS_CREATEANDWAIT:
                    table_row = schedTable_createEntry(table_data,
                                    table_info->indexes->val.string,
                                    table_info->indexes->val_len,
                                    table_info->indexes->next_variable->val.string,
                                    table_info->indexes->next_variable->val_len,
                                    reqinfo->asp->pdu);
                    if (table_row) {
                        netsnmp_insert_table_row(request, table_row);
                    } else {
                        netsnmp_set_request_error(reqinfo, request,
                                                  SNMP_ERR_RESOURCEUNAVAILABLE);
                        return SNMP_ERR_NOERROR;
                    }
                }
            }
        }
        break;

    case MODE_SET_FREE:
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_row = (netsnmp_table_row *)
                netsnmp_extract_table_row(request);
            table_data = netsnmp_extract_table(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDROWSTATUS:
                switch (*request->requestvb->val.integer) {
                case RS_CREATEANDGO:
                case RS_CREATEANDWAIT:
                    if (table_entry && !table_entry->valid) {
                        schedTable_removeEntry(table_data, table_row);
                    }
                }
            }
        }
        break;

    case MODE_SET_ACTION:
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDDESCR:
                memcpy(table_entry->old_schedDescr,
                       table_entry->schedDescr,
                       sizeof(table_entry->schedDescr));
                table_entry->old_schedDescr_len =
                    table_entry->schedDescr_len;
                memset(table_entry->schedDescr, 0,
                       sizeof(table_entry->schedDescr));
                memcpy(table_entry->schedDescr,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                table_entry->schedDescr_len = request->requestvb->val_len;
                break;
            case COLUMN_SCHEDINTERVAL:
                table_entry->old_schedInterval =
                    table_entry->schedInterval;
                table_entry->schedInterval =
                    *request->requestvb->val.integer;
                break;
            case COLUMN_SCHEDWEEKDAY:
                table_entry->old_schedWeekDay =
                    table_entry->schedWeekDay;
                table_entry->schedWeekDay =
                    request->requestvb->val.string[0];
                break;
            case COLUMN_SCHEDMONTH:
                memcpy(table_entry->old_schedMonth,
                       table_entry->schedMonth,
                       sizeof(table_entry->schedMonth));
                memset(table_entry->schedMonth, 0,
                       sizeof(table_entry->schedMonth));
                memcpy(table_entry->schedMonth,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                break;
            case COLUMN_SCHEDDAY:
                memcpy(table_entry->old_schedDay,
                       table_entry->schedDay,
                       sizeof(table_entry->schedDay));
                memset(table_entry->schedDay, 0,
                       sizeof(table_entry->schedDay));
                memcpy(table_entry->schedDay,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                break;
            case COLUMN_SCHEDHOUR:
                memcpy(table_entry->old_schedHour,
                       table_entry->schedHour,
                       sizeof(table_entry->schedHour));
                memset(table_entry->schedHour, 0,
                       sizeof(table_entry->schedHour));
                memcpy(table_entry->schedHour,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                break;
            case COLUMN_SCHEDMINUTE:
                memcpy(table_entry->old_schedMinute,
                       table_entry->schedMinute,
                       sizeof(table_entry->schedMinute));
                memset(table_entry->schedMinute, 0,
                       sizeof(table_entry->schedMinute));
                memcpy(table_entry->schedMinute,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                break;
            case COLUMN_SCHEDCONTEXTNAME:
                memcpy(table_entry->old_schedContextName,
                       table_entry->schedContextName,
                       sizeof(table_entry->schedContextName));
                table_entry->old_schedContextName_len =
                    table_entry->schedContextName_len;
                memset(table_entry->schedContextName, 0,
                       sizeof(table_entry->schedContextName));
                memcpy(table_entry->schedContextName,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                table_entry->schedContextName_len =
                    request->requestvb->val_len;
                break;
            case COLUMN_SCHEDVARIABLE:
                memcpy(table_entry->old_schedVariable,
                       table_entry->schedVariable,
                       sizeof(table_entry->schedVariable));
                table_entry->old_schedVariable_len =
                    table_entry->schedVariable_len;
                memset(table_entry->schedVariable, 0,
                       sizeof(table_entry->schedVariable));
                memcpy(table_entry->schedVariable,
                       request->requestvb->val.string,
                       request->requestvb->val_len);
                table_entry->schedVariable_len =
                    request->requestvb->val_len/sizeof(oid);
                break;
            case COLUMN_SCHEDVALUE:
                table_entry->old_schedValue = table_entry->schedValue;
                table_entry->schedValue = *request->requestvb->val.integer;
                break;
            case COLUMN_SCHEDTYPE:
                table_entry->old_schedType = table_entry->schedType;
                table_entry->schedType = *request->requestvb->val.integer;
                break;
            case COLUMN_SCHEDADMINSTATUS:
                table_entry->old_schedAdminStatus =
                    table_entry->schedAdminStatus;
                table_entry->schedAdminStatus =
                    *request->requestvb->val.integer;
                break;
            case COLUMN_SCHEDSTORAGETYPE:
                table_entry->old_schedStorageType =
                    table_entry->schedStorageType;
                table_entry->schedStorageType =
                    *request->requestvb->val.integer;
                break;
            }
        }
        /*
         * Check the internal consistency of an active row 
         */
#ifdef DTS_TOCHECK
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDROWSTATUS:
                switch (*request->requestvb->val.integer) {
                case RS_ACTIVE:
                case RS_CREATEANDGO:
                    if ( /* XXX */ ) {
                        netsnmp_set_request_error(reqinfo, request,
                                                  SNMP_ERR_INCONSISTENTVALUE);
                        return SNMP_ERR_NOERROR;
                    }
                }
            }
        }
#endif
        break;

    case MODE_SET_UNDO:
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_row = (netsnmp_table_row *)
                netsnmp_extract_table_row(request);
            table_data = netsnmp_extract_table(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDDESCR:
                memcpy(table_entry->schedDescr,
                       table_entry->old_schedDescr,
                       sizeof(table_entry->schedDescr));
                memset(table_entry->old_schedDescr, 0,
                       sizeof(table_entry->schedDescr));
                table_entry->schedDescr_len =
                    table_entry->old_schedDescr_len;
                break;
            case COLUMN_SCHEDINTERVAL:
                table_entry->schedInterval =
                    table_entry->old_schedInterval;
                table_entry->old_schedInterval = 0;
                break;
            case COLUMN_SCHEDWEEKDAY:
                table_entry->schedWeekDay =
                    table_entry->old_schedWeekDay;
                table_entry->old_schedWeekDay = 0;
                break;
            case COLUMN_SCHEDMONTH:
                memcpy(table_entry->schedMonth,
                       table_entry->old_schedMonth,
                       sizeof(table_entry->schedMonth));
                memset(table_entry->old_schedMonth, 0,
                       sizeof(table_entry->schedMonth));
                break;
            case COLUMN_SCHEDDAY:
                memcpy(table_entry->schedDay,
                       table_entry->old_schedDay,
                       sizeof(table_entry->schedDay));
                memset(table_entry->old_schedDay, 0,
                       sizeof(table_entry->schedDay));
                break;
            case COLUMN_SCHEDHOUR:
                memcpy(table_entry->schedHour,
                       table_entry->old_schedHour,
                       sizeof(table_entry->schedHour));
                memset(table_entry->old_schedHour, 0,
                       sizeof(table_entry->schedHour));
                break;
            case COLUMN_SCHEDMINUTE:
                memcpy(table_entry->schedMinute,
                       table_entry->old_schedMinute,
                       sizeof(table_entry->schedMinute));
                memset(table_entry->old_schedMinute, 0,
                       sizeof(table_entry->schedMinute));
                break;
            case COLUMN_SCHEDCONTEXTNAME:
                memcpy(table_entry->schedContextName,
                       table_entry->old_schedContextName,
                       sizeof(table_entry->schedContextName));
                memset(table_entry->old_schedContextName, 0,
                       sizeof(table_entry->schedContextName));
                table_entry->schedContextName_len =
                    table_entry->old_schedContextName_len;
                break;
            case COLUMN_SCHEDVARIABLE:
                memcpy(table_entry->schedVariable,
                       table_entry->old_schedVariable,
                       sizeof(table_entry->schedVariable));
                memset(table_entry->old_schedVariable, 0,
                       sizeof(table_entry->schedVariable));
                table_entry->schedVariable_len =
                    table_entry->old_schedVariable_len;
                break;
            case COLUMN_SCHEDVALUE:
                table_entry->schedValue = table_entry->old_schedValue;
                table_entry->old_schedValue = 0;
                break;
            case COLUMN_SCHEDTYPE:
                table_entry->schedType = table_entry->old_schedType;
                table_entry->old_schedType = 0;
                break;
            case COLUMN_SCHEDADMINSTATUS:
                table_entry->schedAdminStatus =
                    table_entry->old_schedAdminStatus;
                table_entry->old_schedAdminStatus = 0;
                break;
            case COLUMN_SCHEDSTORAGETYPE:
                table_entry->schedStorageType =
                    table_entry->old_schedStorageType;
                table_entry->old_schedStorageType = 0;
                break;
            case COLUMN_SCHEDROWSTATUS:
                switch (*request->requestvb->val.integer) {
                case RS_CREATEANDGO:
                case RS_CREATEANDWAIT:
                    if (table_entry && !table_entry->valid) {
                        schedTable_removeEntry(table_data, table_row);
                    }
                }
                break;
            }
        }
        break;

    case MODE_SET_COMMIT:
        for (request = requests; request; request = request->next) {
            table_entry = (struct schedTable_entry *)
                netsnmp_extract_table_row_data(request);
            table_row = (netsnmp_table_row *)
                netsnmp_extract_table_row(request);
            table_data = netsnmp_extract_table(request);
            table_info = netsnmp_extract_table_info(request);

            switch (table_info->colnum) {
            case COLUMN_SCHEDROWSTATUS:
                switch (*request->requestvb->val.integer) {
                case RS_CREATEANDGO:
                    table_entry->valid = 1;
                    /*
                     * Fall-through 
                     */
                case RS_ACTIVE:
                    table_entry->schedRowStatus = RS_ACTIVE;
                    break;

                case RS_CREATEANDWAIT:
                    table_entry->valid = 1;
                    /*
                     * Fall-through 
                     */
                case RS_NOTINSERVICE:
                    table_entry->schedRowStatus = RS_NOTINSERVICE;
                    break;

                case RS_DESTROY:
                    schedTable_removeEntry(table_data, table_row);
                }
                recalculate = 1;
                break;

            case COLUMN_SCHEDINTERVAL:
            case COLUMN_SCHEDWEEKDAY:
            case COLUMN_SCHEDMONTH:
            case COLUMN_SCHEDDAY:
            case COLUMN_SCHEDHOUR:
            case COLUMN_SCHEDMINUTE:
            case COLUMN_SCHEDTYPE:
            case COLUMN_SCHEDADMINSTATUS:
                recalculate = 1;
                break;
            }
        }
        if (recalculate)
            sched_nextTime(table_entry);
        break;
    }
    return SNMP_ERR_NOERROR;
}
