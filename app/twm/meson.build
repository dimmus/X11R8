ver_twm = '1.0.12'

conf.set_quoted('APP_VERSION', ver_twm)
conf.set_quoted('DATA_DIR', dir_data)
conf.set('HAVE_XRANDR', 1)

f_check += ['mkstemp']

twm_dependencies = [
    libx11,
    libxext,
    libxt,
    libxmu,
    libice,
    libsm,
    libxrandr,
    libi18n,
    libxkbfile,
    xproto,
]

subdir('src')
