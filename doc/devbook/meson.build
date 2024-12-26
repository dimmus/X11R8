require_docs = get_option('docs') == 'true'
require_devel_docs = get_option('devel-docs') == 'true'
require_docs_pdf = (require_docs or require_devel_docs) and get_option('docs-pdf') == 'true'

dep_sgml_doctools = dependency('xorg-sgml-doctools',
                               required: require_docs or require_devel_docs)

build_docs = (get_option('docs') != 'false' and
              dep_sgml_doctools.found() and xmlto.found())

build_docs_devel = (get_option('devel-docs') != 'false' and
                    dep_sgml_doctools.found() and xmlto.found())

build_docs_pdf = (get_option('docs-pdf') != 'false' and
                 (build_docs or build_docs_devel) and fop.found())

if build_docs or build_docs_devel
    doc_sgml_path = dep_sgml_doctools.get_variable(pkgconfig: 'sgmlrootdir')
    doc_stylesheet_srcdir = doc_sgml_path / 'X11'

    # Meson does not and will not support functions so we are copy-pasting
    # documentation build code around which is unfortunate
    # See https://mesonbuild.com/FAQ.html#why-doesnt-meson-have-user-defined-functionsmacros

    docs_xmlto_search_flags = [
        '--searchpath', doc_stylesheet_srcdir,
        '--searchpath', meson.project_build_root(),
    ]

    docs_xslt_search_flags = [
        '--path', doc_stylesheet_srcdir,
        '--path', meson.project_build_root(),
    ]
endif