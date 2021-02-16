#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H

struct yy_buffer_state;

using YY_BUFFER_STATE = yy_buffer_state*;

void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );
YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );
void yy_delete_buffer ( YY_BUFFER_STATE b  );

#endif
