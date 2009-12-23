
ADD_LIBRARY( grammar_attribute STATIC grammar/attribute.cpp )

ADD_LIBRARY( grammar_xcb STATIC grammar/xcb.cpp )
TARGET_LINK_LIBRARIES( grammar_xcb grammar_attribute grammar_macro )

ADD_LIBRARY( grammar_pad STATIC grammar/pad.cpp )
TARGET_LINK_LIBRARIES( grammar_pad grammar_attribute )

ADD_LIBRARY( grammar_var STATIC grammar/var.cpp )
TARGET_LINK_LIBRARIES( grammar_var grammar_attribute )

ADD_LIBRARY( grammar_field STATIC grammar/field.cpp )
TARGET_LINK_LIBRARIES( grammar_xcb grammar_var )

ADD_LIBRARY( grammar_list STATIC grammar/list.cpp )
TARGET_LINK_LIBRARIES( grammar_list grammar_var )

ADD_LIBRARY( grammar_op STATIC grammar/op.cpp )
TARGET_LINK_LIBRARIES( grammar_op grammar_attribute )

ADD_LIBRARY( grammar_fieldref STATIC grammar/fieldref.cpp )

ADD_LIBRARY( grammar_value STATIC grammar/value.cpp )

ADD_LIBRARY( grammar_bit STATIC grammar/bit.cpp )

ADD_LIBRARY( grammar_expression STATIC grammar/expression.cpp )
TARGET_LINK_LIBRARIES( grammar_expression grammar_op grammar_fieldref grammar_value grammar_bit )


