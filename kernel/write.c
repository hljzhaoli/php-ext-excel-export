/*
  +----------------------------------------------------------------------+
  | XlsWriter Extension                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 2017-2018 The Viest                                    |
  +----------------------------------------------------------------------+
  | http://www.viest.me                                                  |
  +----------------------------------------------------------------------+
  | Author: viest <dev@service.viest.me>                                 |
  +----------------------------------------------------------------------+
*/

#include "xlswriter.h"

/*
 * According to the zval type written to the file
 */
void type_writer(zval *value, zend_long row, zend_long columns, xls_resource_write_t *res, zend_string *format, lxw_format *format_handle)
{
    lxw_format *value_format = NULL;

    lxw_col_t lxw_col = (lxw_col_t)columns;
    lxw_row_t lxw_row = (lxw_row_t)row;

    zend_uchar value_type = Z_TYPE_P(value);

    if (value_type == IS_STRING) {
        zend_string *_zstr_val = zval_get_string(value);
        worksheet_write_string(res->worksheet, lxw_row, lxw_col, ZSTR_VAL(_zstr_val), format_handle);
        zend_string_release(_zstr_val);
        return;
    }

    if (value_type == IS_LONG) {
        if (format != NULL && format_handle == NULL) {
            value_format = workbook_add_format(res->workbook);

            format_set_num_format(value_format, ZSTR_VAL(format));

            worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_long(value), value_format);
            return;
        }

        if (format == NULL && format_handle != NULL) {
            worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_long(value), format_handle);
            return;
        }

        if(format != NULL && format_handle != NULL) {
            value_format = workbook_add_format(res->workbook);

            format_copy(value_format, format_handle);
            format_set_num_format(value_format, ZSTR_VAL(format));

            worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_long(value), value_format);
            return;
        }

        worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_long(value), NULL);
    }

    if (value_type == IS_DOUBLE) {
        if (format != NULL && format_handle == NULL) {
            value_format = workbook_add_format(res->workbook);

            format_set_num_format(value_format, ZSTR_VAL(format));

            worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_double(value), value_format);
            return;
        }

        if (format == NULL && format_handle != NULL) {
            worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_double(value), format_handle);
            return;
        }

        if(format != NULL && format_handle != NULL) {
            value_format = workbook_add_format(res->workbook);

            format_copy(value_format, format_handle);
            format_set_num_format(value_format, ZSTR_VAL(format));

            worksheet_write_number(res->worksheet, lxw_row, lxw_col, zval_get_double(value), value_format);
            return;
        }

        worksheet_write_number(res->worksheet, row, columns, zval_get_double(value), NULL);
        return;
    }
}

void format_copy(lxw_format *new_format, lxw_format *other_format)
{
    new_format->bold = other_format->bold;
    new_format->bg_color = other_format->bg_color;
    new_format->border_count = other_format->border_count;
    new_format->border_index = other_format->border_index;
    new_format->bottom = other_format->bottom;
    new_format->bottom_color = other_format->bottom_color;
    new_format->color_indexed = other_format->color_indexed;
    new_format->diag_border = other_format->diag_border;
    new_format->diag_color = other_format->diag_color;

    new_format->font_size = other_format->font_size;
    new_format->bold = other_format->bold;
    new_format->italic = other_format->italic;
    new_format->font_color = other_format->font_color;
    new_format->underline = other_format->underline;
    new_format->font_strikeout = other_format->font_strikeout;
    new_format->font_outline = other_format->font_outline;
    new_format->font_shadow = other_format->font_shadow;
    new_format->font_script = other_format->font_script;
    new_format->font_family = other_format->font_family;
    new_format->font_charset = other_format->font_charset;
    new_format->font_condense = other_format->font_condense;
    new_format->font_extend = other_format->font_extend;
    new_format->theme = other_format->theme;
    new_format->hyperlink = other_format->hyperlink;

    new_format->hidden = other_format->hidden;
    new_format->locked = other_format->locked;

    new_format->text_h_align = other_format->text_h_align;
    new_format->text_wrap = other_format->text_wrap;
    new_format->text_v_align = other_format->text_v_align;
    new_format->text_justlast = other_format->text_justlast;
    new_format->rotation = other_format->rotation;

    new_format->fg_color = other_format->fg_color;
    new_format->bg_color = other_format->bg_color;
    new_format->pattern = other_format->pattern;
    new_format->has_fill = other_format->has_fill;
    new_format->has_dxf_fill = other_format->has_dxf_fill;
    new_format->fill_index = other_format->fill_index;
    new_format->fill_count = other_format->fill_count;

    new_format->border_index = other_format->border_index;
    new_format->has_border = other_format->has_border;
    new_format->has_dxf_border = other_format->has_dxf_border;
    new_format->border_count = other_format->border_count;

    new_format->bottom = other_format->bottom;
    new_format->diag_border = other_format->diag_border;
    new_format->diag_type = other_format->diag_type;
    new_format->left = other_format->left;
    new_format->right = other_format->right;
    new_format->top = other_format->top;
    new_format->bottom_color = other_format->bottom_color;
    new_format->diag_color = other_format->diag_color;
    new_format->left_color = other_format->left_color;
    new_format->right_color = other_format->right_color;
    new_format->top_color = other_format->top_color;

    new_format->indent = other_format->indent;
    new_format->shrink = other_format->shrink;
    new_format->merge_range = other_format->merge_range;
    new_format->reading_order = other_format->reading_order;
    new_format->just_distrib = other_format->just_distrib;
    new_format->color_indexed = other_format->color_indexed;
    new_format->font_only = other_format->font_only;
}

void url_writer(zend_long row, zend_long columns, xls_resource_write_t *res, zend_string *url, lxw_format *format)
{
    worksheet_write_url(res->worksheet, row, columns, ZSTR_VAL(url), format);
}

/*
 * Write the image to the file
 */
void image_writer(zval *value, zend_long row, zend_long columns, double width, double height, xls_resource_write_t *res)
{
    lxw_image_options options = {.x_scale = width, .y_scale = height};

    worksheet_insert_image_opt(res->worksheet, row, columns, ZSTR_VAL(zval_get_string(value)), &options);
}

/*
 * Write the image to the file
 */
void formula_writer(zval *value, zend_long row, zend_long columns, xls_resource_write_t *res)
{
    worksheet_write_formula(res->worksheet, row, columns, ZSTR_VAL(zval_get_string(value)), NULL);
}

void chart_writer(zend_long row, zend_long columns, xls_resource_chart_t *chart_resource, xls_resource_write_t *res)
{
    worksheet_insert_chart(res->worksheet, row, columns, chart_resource->chart);
}

/*
 * Add the autofilter.
 */
void auto_filter(zend_string *range, xls_resource_write_t *res)
{
    worksheet_autofilter(res->worksheet, RANGE(ZSTR_VAL(range)));
}

/*
 * Merge cells.
 */
void merge_cells(zend_string *range, zend_string *value, xls_resource_write_t *res)
{
    worksheet_merge_range(res->worksheet, RANGE(ZSTR_VAL(range)), ZSTR_VAL(value), NULL);
}

/*
 * Set column format
 */
void set_column(zend_string *range, double width, xls_resource_write_t *res, lxw_format *format)
{
    worksheet_set_column(res->worksheet, COLS(ZSTR_VAL(range)), width, format);
}

/*
 * Set row format
 */
void set_row(zend_string *range, double height, xls_resource_write_t *res, lxw_format *format)
{
    char *rows = ZSTR_VAL(range);

    if (strchr(rows, ':')) {
        worksheet_set_rows(ROWS(rows), height, res, format);
    } else {
        worksheet_set_row(res->worksheet, ROW(rows), height, format);
    }
}

/*
 * Set rows format
 */
void worksheet_set_rows(lxw_row_t start, lxw_row_t end, double height, xls_resource_write_t *res, lxw_format *format)
{
    while (1) {
        worksheet_set_row(res->worksheet, end, height, format);
        if (end == start)
            break;
        end--;
    }
}

/*
 * Call finalization code and close file.
 */
lxw_error
workbook_file(xls_resource_write_t *self)
{
    lxw_worksheet *worksheet = NULL;
    lxw_packager *packager = NULL;
    lxw_error error = LXW_NO_ERROR;

    /* Add a default worksheet if non have been added. */
    if (!self->workbook->num_sheets)
        workbook_add_worksheet(self->workbook, NULL);

    /* Ensure that at least one worksheet has been selected. */
    if (self->workbook->active_sheet == 0) {
        worksheet = STAILQ_FIRST(self->workbook->worksheets);
        worksheet->selected = 1;
        worksheet->hidden = 0;
    }

    /* Set the active sheet. */
    STAILQ_FOREACH(worksheet, self->workbook->worksheets, list_pointers) {
        if (worksheet->index == self->workbook->active_sheet)
            worksheet->active = 1;
    }

    /* Set the defined names for the worksheets such as Print Titles. */
    _prepare_defined_names(self->workbook);

    /* Prepare the drawings, charts and images. */
    _prepare_drawings(self->workbook);

    /* Add cached data to charts. */
    _add_chart_cache_data(self->workbook);

/* ugly test, new param (use_zip_64) was added in 0.8.7 with workbook_add_vba_project */
#ifdef HAVE_WORKBOOK_ADD_VBA_PROJECT
    /* Create a packager object to assemble sub-elements into a zip file. */
    packager = lxw_packager_new(self->workbook->filename, self->workbook->options.tmpdir, 0);
#else
    packager = lxw_packager_new(self->workbook->filename, self->workbook->options.tmpdir);
#endif

    /* If the packager fails it is generally due to a zip permission error. */
    if (packager == NULL) {
        fprintf(stderr, "[ERROR] workbook_close(): "
                "Error creating '%s'. "
                "Error = %s\n", self->workbook->filename, strerror(errno));

        error = LXW_ERROR_CREATING_XLSX_FILE;
        goto mem_error;
    }

    /* Set the workbook object in the packager. */
    packager->workbook = self->workbook;

    /* Assemble all the sub-files in the xlsx package. */
    error = lxw_create_package(packager);

    /* Error and non-error conditions fall through to the cleanup code. */
    if (error == LXW_ERROR_CREATING_TMPFILE) {
        fprintf(stderr, "[ERROR] workbook_close(): "
                "Error creating tmpfile(s) to assemble '%s'. "
                "Error = %s\n", self->workbook->filename, strerror(errno));
    }

    /* If LXW_ERROR_ZIP_FILE_OPERATION then errno is set by zlib. */
    if (error == LXW_ERROR_ZIP_FILE_OPERATION) {
        fprintf(stderr, "[ERROR] workbook_close(): "
                "Zlib error while creating xlsx file '%s'. "
                "Error = %s\n", self->workbook->filename, strerror(errno));
    }

    /* The next 2 error conditions don't set errno. */
    if (error == LXW_ERROR_ZIP_FILE_ADD) {
        fprintf(stderr, "[ERROR] workbook_close(): "
                        "Zlib error adding file to xlsx file '%s'.\n",
                self->workbook->filename);
    }

    if (error == LXW_ERROR_ZIP_CLOSE) {
        fprintf(stderr, "[ERROR] workbook_close(): "
                "Zlib error closing xlsx file '%s'.\n", self->workbook->filename);
    }

    mem_error:
        lxw_packager_free(packager);

    return error;
}

void _php_vtiful_xls_close(zend_resource *rsrc TSRMLS_DC)
{

}

/*
 * Iterate through the worksheets and store any defined names used for print
 * ranges or repeat rows/columns.
 */
STATIC void
_prepare_defined_names(lxw_workbook *self)
{
    lxw_worksheet *worksheet;
    char app_name[LXW_DEFINED_NAME_LENGTH];
    char range[LXW_DEFINED_NAME_LENGTH];
    char area[LXW_MAX_CELL_RANGE_LENGTH];
    char first_col[8];
    char last_col[8];

    STAILQ_FOREACH(worksheet, self->worksheets, list_pointers) {

        /*
         * Check for autofilter settings and store them.
         */
        if (worksheet->autofilter.in_use) {

            lxw_snprintf(app_name, LXW_DEFINED_NAME_LENGTH,
                         "%s!_FilterDatabase", worksheet->quoted_name);

            lxw_rowcol_to_range_abs(area,
                                    worksheet->autofilter.first_row,
                                    worksheet->autofilter.first_col,
                                    worksheet->autofilter.last_row,
                                    worksheet->autofilter.last_col);

            lxw_snprintf(range, LXW_DEFINED_NAME_LENGTH, "%s!%s",
                         worksheet->quoted_name, area);

            /* Autofilters are the only defined name to set the hidden flag. */
            _store_defined_name(self, "_xlnm._FilterDatabase", app_name, range, worksheet->index, LXW_TRUE);
        }

        /*
         * Check for Print Area settings and store them.
         */
        if (worksheet->print_area.in_use) {

            lxw_snprintf(app_name, LXW_DEFINED_NAME_LENGTH,
                         "%s!Print_Area", worksheet->quoted_name);

            /* Check for print area that is the max row range. */
            if (worksheet->print_area.first_row == 0
                && worksheet->print_area.last_row == LXW_ROW_MAX - 1) {

                lxw_col_to_name(first_col,
                                worksheet->print_area.first_col, LXW_FALSE);

                lxw_col_to_name(last_col,
                                worksheet->print_area.last_col, LXW_FALSE);

                lxw_snprintf(area, LXW_MAX_CELL_RANGE_LENGTH - 1, "$%s:$%s",
                             first_col, last_col);

            }
                /* Check for print area that is the max column range. */
            else if (worksheet->print_area.first_col == 0
                     && worksheet->print_area.last_col == LXW_COL_MAX - 1) {

                lxw_snprintf(area, LXW_MAX_CELL_RANGE_LENGTH - 1, "$%d:$%d",
                             worksheet->print_area.first_row + 1,
                             worksheet->print_area.last_row + 1);

            }
            else {
                lxw_rowcol_to_range_abs(area,
                                        worksheet->print_area.first_row,
                                        worksheet->print_area.first_col,
                                        worksheet->print_area.last_row,
                                        worksheet->print_area.last_col);
            }

            lxw_snprintf(range, LXW_DEFINED_NAME_LENGTH, "%s!%s",
                         worksheet->quoted_name, area);

            _store_defined_name(self, "_xlnm.Print_Area", app_name,
                                range, worksheet->index, LXW_FALSE);
        }

        /*
         * Check for repeat rows/cols. aka, Print Titles and store them.
         */
        if (worksheet->repeat_rows.in_use || worksheet->repeat_cols.in_use) {
            if (worksheet->repeat_rows.in_use
                && worksheet->repeat_cols.in_use) {
                lxw_snprintf(app_name, LXW_DEFINED_NAME_LENGTH,
                             "%s!Print_Titles", worksheet->quoted_name);

                lxw_col_to_name(first_col,
                                worksheet->repeat_cols.first_col, LXW_FALSE);

                lxw_col_to_name(last_col,
                                worksheet->repeat_cols.last_col, LXW_FALSE);

                lxw_snprintf(range, LXW_DEFINED_NAME_LENGTH,
                             "%s!$%s:$%s,%s!$%d:$%d",
                             worksheet->quoted_name, first_col,
                             last_col, worksheet->quoted_name,
                             worksheet->repeat_rows.first_row + 1,
                             worksheet->repeat_rows.last_row + 1);

                _store_defined_name(self, "_xlnm.Print_Titles", app_name,
                                    range, worksheet->index, LXW_FALSE);
            }
            else if (worksheet->repeat_rows.in_use) {

                lxw_snprintf(app_name, LXW_DEFINED_NAME_LENGTH,
                             "%s!Print_Titles", worksheet->quoted_name);

                lxw_snprintf(range, LXW_DEFINED_NAME_LENGTH,
                             "%s!$%d:$%d", worksheet->quoted_name,
                             worksheet->repeat_rows.first_row + 1,
                             worksheet->repeat_rows.last_row + 1);

                _store_defined_name(self, "_xlnm.Print_Titles", app_name,
                                    range, worksheet->index, LXW_FALSE);
            }
            else if (worksheet->repeat_cols.in_use) {
                lxw_snprintf(app_name, LXW_DEFINED_NAME_LENGTH,
                             "%s!Print_Titles", worksheet->quoted_name);

                lxw_col_to_name(first_col,
                                worksheet->repeat_cols.first_col, LXW_FALSE);

                lxw_col_to_name(last_col,
                                worksheet->repeat_cols.last_col, LXW_FALSE);

                lxw_snprintf(range, LXW_DEFINED_NAME_LENGTH,
                             "%s!$%s:$%s", worksheet->quoted_name,
                             first_col, last_col);

                _store_defined_name(self, "_xlnm.Print_Titles", app_name,
                                    range, worksheet->index, LXW_FALSE);
            }
        }
    }
}

/*
 * Iterate through the worksheets and set up any chart or image drawings.
 */
STATIC void
_prepare_drawings(lxw_workbook *self)
{
    lxw_worksheet *worksheet;
    lxw_image_options *image_options;
    uint16_t chart_ref_id = 0;
    uint16_t image_ref_id = 0;
    uint16_t drawing_id = 0;

    STAILQ_FOREACH(worksheet, self->worksheets, list_pointers) {

        if (STAILQ_EMPTY(worksheet->image_data)
            && STAILQ_EMPTY(worksheet->chart_data))
            continue;

        drawing_id++;

        STAILQ_FOREACH(image_options, worksheet->chart_data, list_pointers) {
            chart_ref_id++;
#ifdef HAVE_LXW_CHARTSHEET_NEW
            lxw_worksheet_prepare_chart(worksheet, chart_ref_id, drawing_id,
                                        image_options, 0);
#else
            lxw_worksheet_prepare_chart(worksheet, chart_ref_id, drawing_id,
                                        image_options);
#endif
            if (image_options->chart)
                STAILQ_INSERT_TAIL(self->ordered_charts, image_options->chart,
                                   ordered_list_pointers);
        }

        STAILQ_FOREACH(image_options, worksheet->image_data, list_pointers) {

            if (image_options->image_type == LXW_IMAGE_PNG)
                self->has_png = LXW_TRUE;

            if (image_options->image_type == LXW_IMAGE_JPEG)
                self->has_jpeg = LXW_TRUE;

            if (image_options->image_type == LXW_IMAGE_BMP)
                self->has_bmp = LXW_TRUE;

            image_ref_id++;

            lxw_worksheet_prepare_image(worksheet, image_ref_id, drawing_id,
                                        image_options);
        }
    }

    self->drawing_count = drawing_id;
}

/*
 * Add "cached" data to charts to provide the numCache and strCache data for
 * series and title/axis ranges.
 */
STATIC void
_add_chart_cache_data(lxw_workbook *self)
{
    lxw_chart *chart;
    lxw_chart_series *series;

    STAILQ_FOREACH(chart, self->ordered_charts, ordered_list_pointers) {

        _populate_range(self, chart->title.range);
        _populate_range(self, chart->x_axis->title.range);
        _populate_range(self, chart->y_axis->title.range);

        if (STAILQ_EMPTY(chart->series_list))
            continue;

        STAILQ_FOREACH(series, chart->series_list, list_pointers) {
            _populate_range(self, series->categories);
            _populate_range(self, series->values);
            _populate_range(self, series->title.range);
        }
    }
}

/*
 * Process and store the defined names. The defined names are stored with
 * the Workbook.xml but also with the App.xml if they refer to a sheet
 * range like "Sheet1!:A1". The defined names are store in sorted
 * order for consistency with Excel. The names need to be normalized before
 * sorting.
 */
STATIC lxw_error
_store_defined_name(lxw_workbook *self, const char *name, const char *app_name, const char *formula, int16_t index, uint8_t hidden)
{
    lxw_worksheet *worksheet;
    lxw_defined_name *defined_name;
    lxw_defined_name *list_defined_name;
    char name_copy[LXW_DEFINED_NAME_LENGTH];
    char *tmp_str;
    char *worksheet_name;

    /* Do some checks on the input data */
    if (!name || !formula)
        return LXW_ERROR_NULL_PARAMETER_IGNORED;

    if (lxw_utf8_strlen(name) > LXW_DEFINED_NAME_LENGTH ||
        lxw_utf8_strlen(formula) > LXW_DEFINED_NAME_LENGTH) {
        return LXW_ERROR_128_STRING_LENGTH_EXCEEDED;
    }

    /* Allocate a new defined_name to be added to the linked list of names. */
    defined_name = calloc(1, sizeof(struct lxw_defined_name));
    RETURN_ON_MEM_ERROR(defined_name, LXW_ERROR_MEMORY_MALLOC_FAILED);

    /* Copy the user input string. */
    lxw_strcpy(name_copy, name);

    /* Set the worksheet index or -1 for a global defined name. */
    defined_name->index = index;
    defined_name->hidden = hidden;

    /* Check for local defined names like like "Sheet1!name". */
    tmp_str = strchr(name_copy, '!');

    if (tmp_str == NULL) {
        /* The name is global. We just store the defined name string. */
        lxw_strcpy(defined_name->name, name_copy);
    }
    else {
        /* The name is worksheet local. We need to extract the sheet name
         * and map it to a sheet index. */

        /* Split the into the worksheet name and defined name. */
        *tmp_str = '\0';
        tmp_str++;
        worksheet_name = name_copy;

        /* Remove any worksheet quoting. */
        if (worksheet_name[0] == '\'')
            worksheet_name++;
        if (worksheet_name[strlen(worksheet_name) - 1] == '\'')
            worksheet_name[strlen(worksheet_name) - 1] = '\0';

        /* Search for worksheet name to get the equivalent worksheet index. */
        STAILQ_FOREACH(worksheet, self->worksheets, list_pointers) {
            if (strcmp(worksheet_name, worksheet->name) == 0) {
                defined_name->index = worksheet->index;
                lxw_strcpy(defined_name->normalised_sheetname,
                           worksheet_name);
            }
        }

        /* If we didn't find the worksheet name we exit. */
        if (defined_name->index == -1)
            goto mem_error;

        lxw_strcpy(defined_name->name, tmp_str);
    }

    /* Print titles and repeat title pass in the name used for App.xml. */
    if (app_name) {
        lxw_strcpy(defined_name->app_name, app_name);
        lxw_strcpy(defined_name->normalised_sheetname, app_name);
    }
    else {
        lxw_strcpy(defined_name->app_name, name);
    }

    /* We need to normalize the defined names for sorting. This involves
     * removing any _xlnm namespace  and converting it to lowercase. */
    tmp_str = strstr(name_copy, "_xlnm.");

    if (tmp_str)
        lxw_strcpy(defined_name->normalised_name, defined_name->name + 6);
    else
        lxw_strcpy(defined_name->normalised_name, defined_name->name);

    lxw_str_tolower(defined_name->normalised_name);
    lxw_str_tolower(defined_name->normalised_sheetname);

    /* Strip leading "=" from the formula. */
    if (formula[0] == '=')
        lxw_strcpy(defined_name->formula, formula + 1);
    else
        lxw_strcpy(defined_name->formula, formula);

    /* We add the defined name to the list in sorted order. */
    list_defined_name = TAILQ_FIRST(self->defined_names);

    if (list_defined_name == NULL ||
        _compare_defined_names(defined_name, list_defined_name) < 1) {
        /* List is empty or defined name goes to the head. */
        TAILQ_INSERT_HEAD(self->defined_names, defined_name, list_pointers);
        return LXW_NO_ERROR;
    }

    TAILQ_FOREACH(list_defined_name, self->defined_names, list_pointers) {
        int res = _compare_defined_names(defined_name, list_defined_name);

        /* The entry already exists. We exit and don't overwrite. */
        if (res == 0)
            goto mem_error;

        /* New defined name is inserted in sorted order before other entries. */
        if (res < 0) {
            TAILQ_INSERT_BEFORE(list_defined_name, defined_name,
                                list_pointers);
            return LXW_NO_ERROR;
        }
    }

    /* If the entry wasn't less than any of the entries in the list we add it
     * to the end. */
    TAILQ_INSERT_TAIL(self->defined_names, defined_name, list_pointers);
    return LXW_NO_ERROR;

    mem_error:
    free(defined_name);
    return LXW_ERROR_MEMORY_MALLOC_FAILED;
}

/*
 * Compare two defined_name structures.
 */
static int
_compare_defined_names(lxw_defined_name *a, lxw_defined_name *b)
{
    int res = strcmp(a->normalised_name, b->normalised_name);

    /* Primary comparison based on defined name. */
    if (res)
        return res;

    /* Secondary comparison based on worksheet name. */
    res = strcmp(a->normalised_sheetname, b->normalised_sheetname);

    return res;
}

/* Convert a chart range such as Sheet1!$A$1:$A$5 to a sheet name and row-col
 * dimensions, or vice-versa. This gives us the dimensions to read data back
 * from the worksheet.
 */
STATIC void
_populate_range_dimensions(lxw_workbook *self, lxw_series_range *range)
{

    char formula[LXW_MAX_FORMULA_RANGE_LENGTH] = { 0 };
    char *tmp_str;
    char *sheetname;

    /* If neither the range formula or sheetname is defined then this probably
     * isn't a valid range.
     */
    if (!range->formula && !range->sheetname) {
        range->ignore_cache = LXW_TRUE;
        return;
    }

    /* If the sheetname is already defined it was already set via
     * chart_series_set_categories() or  chart_series_set_values().
     */
    if (range->sheetname)
        return;

    /* Ignore non-contiguous range like (Sheet1!$A$1:$A$2,Sheet1!$A$4:$A$5) */
    if (range->formula[0] == '(') {
        range->ignore_cache = LXW_TRUE;
        return;
    }

    /* Create a copy of the formula to modify and parse into parts. */
    lxw_snprintf(formula, LXW_MAX_FORMULA_RANGE_LENGTH, "%s", range->formula);

    /* Check for valid formula. TODO. This needs stronger validation. */
    tmp_str = strchr(formula, '!');

    if (tmp_str == NULL) {
        range->ignore_cache = LXW_TRUE;
        return;
    }
    else {
        /* Split the formulas into sheetname and row-col data. */
        *tmp_str = '\0';
        tmp_str++;
        sheetname = formula;

        /* Remove any worksheet quoting. */
        if (sheetname[0] == '\'')
            sheetname++;
        if (sheetname[strlen(sheetname) - 1] == '\'')
            sheetname[strlen(sheetname) - 1] = '\0';

        /* Check that the sheetname exists. */
        if (!workbook_get_worksheet_by_name(self, sheetname)) {
            LXW_WARN_FORMAT2("workbook_add_chart(): worksheet name '%s' "
                                     "in chart formula '%s' doesn't exist.",
                             sheetname, range->formula);
            range->ignore_cache = LXW_TRUE;
            return;
        }

        range->sheetname = lxw_strdup(sheetname);
        range->first_row = lxw_name_to_row(tmp_str);
        range->first_col = lxw_name_to_col(tmp_str);

        if (strchr(tmp_str, ':')) {
            /* 2D range. */
            range->last_row = lxw_name_to_row_2(tmp_str);
            range->last_col = lxw_name_to_col_2(tmp_str);
        }
        else {
            /* 1D range. */
            range->last_row = range->first_row;
            range->last_col = range->first_col;
        }

    }
}

/*
 * Populate the data cache of a chart data series by reading the data from the
 * relevant worksheet and adding it to the cached in the range object as a
 * list of points.
 *
 * Note, the data cache isn't strictly required by Excel but it helps if the
 * chart is embedded in another application such as PowerPoint and it also
 * helps with comparison testing.
 */
STATIC void
_populate_range_data_cache(lxw_workbook *self, lxw_series_range *range)
{
    lxw_worksheet *worksheet;
    lxw_row_t row_num;
    lxw_col_t col_num;
    lxw_row *row_obj;
    lxw_cell *cell_obj;
    struct lxw_series_data_point *data_point;
    uint16_t num_data_points = 0;

    /* If ignore_cache is set then don't try to populate the cache. This flag
     * may be set manually, for testing, or due to a case where the cache
     * can't be calculated.
     */
    if (range->ignore_cache)
        return;

    /* Currently we only handle 2D ranges so ensure either the rows or cols
     * are the same.
     */
    if (range->first_row != range->last_row
        && range->first_col != range->last_col) {
        range->ignore_cache = LXW_TRUE;
        return;
    }

    /* Check that the sheetname exists. */
    worksheet = workbook_get_worksheet_by_name(self, range->sheetname);
    if (!worksheet) {
        LXW_WARN_FORMAT2("workbook_add_chart(): worksheet name '%s' "
                                 "in chart formula '%s' doesn't exist.",
                         range->sheetname, range->formula);
        range->ignore_cache = LXW_TRUE;
        return;
    }

    /* We can't read the data when worksheet optimization is on. */
    if (worksheet->optimize) {
        range->ignore_cache = LXW_TRUE;
        return;
    }

    /* Iterate through the worksheet data and populate the range cache. */
    for (row_num = range->first_row; row_num <= range->last_row; row_num++) {
        row_obj = lxw_worksheet_find_row(worksheet, row_num);

        for (col_num = range->first_col; col_num <= range->last_col;
             col_num++) {

            data_point = calloc(1, sizeof(struct lxw_series_data_point));
            if (!data_point) {
                range->ignore_cache = LXW_TRUE;
                return;
            }

            cell_obj = lxw_worksheet_find_cell(row_obj, col_num);

            if (cell_obj) {
                if (cell_obj->type == NUMBER_CELL) {
                    data_point->number = cell_obj->u.number;
                }

                if (cell_obj->type == STRING_CELL) {
                    data_point->string = lxw_strdup(cell_obj->sst_string);
                    data_point->is_string = LXW_TRUE;
                    range->has_string_cache = LXW_TRUE;
                }
            }
            else {
                data_point->no_data = LXW_TRUE;
            }

            STAILQ_INSERT_TAIL(range->data_cache, data_point, list_pointers);
            num_data_points++;
        }
    }

    range->num_data_points = num_data_points;
}

/* Set the range dimensions and set the data cache.
 */
STATIC void
_populate_range(lxw_workbook *self, lxw_series_range *range)
{
    _populate_range_dimensions(self, range);
    _populate_range_data_cache(self, range);
}
