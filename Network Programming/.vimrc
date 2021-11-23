set nocompatible
filetype off 

set laststatus=2
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'arcticicestudio/nord-vim'
Plugin 'ayu-theme/ayu-vim'
Plugin 'AlessandroYorba/Alduin'
Plugin 'romainl/Apprentice'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'Valloric/YouCompleteMe'
Plugin 'airblade/vim-gitgutter'
Plugin 'junegunn/fzf.vim'
Plugin 'tpope/vim-surround'
Plugin 'raphamorim/lucario'
Plugin 'morhetz/gruvbox'
Plugin 'ianding1/leetcode.vim'

call vundle#end()            " required
filetype plugin indent on

syntax enable
syntax on

set autoindent
set smartindent
set cindent
set number
set ruler
set ttyfast
set tabstop=4
set shiftwidth=4
set expandtab
set showmatch

let g:indent_guides_guide_size = 1 
let g:indent_guides_color_change_percent = 3 
let g:indent_guides_enable_on_vim_startup = 1 
let g:airline#extensions#tabline#enabled = 1 
let g:airline#extensions#tabline#left_sep = ' ' 
let g:airline#extensions#tabline#left_alt_sep = '|' 
let g:airline#extensions#tabline#show_tab_nr = 1 
let g:airline#extensions#tabline#tab_nr_type= 2
let g:airline#extensions#tabline#show_tab_type = 1 
let g:airline_highlighting_cache = 1 
let g:airline_theme='ayu'
let g:airline#extensions#tabline#formatter='unique_tail_improved'
let g:airline#extensions#tabline#wrap = 0
let g:airline_powerline_fonts=1
let g:gruvbox_contrast_dark='hard'
let g:ycm_global_ycm_extra_conf = '~/.ycm_extra_conf.py'
let g:leetcode_browser = 'chrome'

if !exists('g:airline_symbols')
    let g:airline_symbols = {}
endif

" unicode symbols
let g:airline_left_sep = '»'
let g:airline_left_sep = '▶'
let g:airline_right_sep = '«'
let g:airline_right_sep = '◀'
let g:airline_symbols.linenr = '␊'
let g:airline_symbols.linenr = '␤'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.branch = '⎇'
let g:airline_symbols.paste = 'ρ'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.paste = '∥'
let g:airline_symbols.whitespace = 'Ξ'

" IndentLine {{
let g:indentLine_char = '⎸'
let g:indentLine_first_char = '⎸'
let g:indentLine_showFirstIndentLevel = 1
let g:indentLine_setColors = 239
" }}

" colors - mirage,light,dark
"let g:alduin_Shout_Become_Ethereal = 1
"colorscheme alduin

"set ayucolor="dark"   " for dark version of theme
colorscheme gruvbox
set termguicolors     " enable true colors support
let &t_8f = "\<Esc>[38;2;%lu;%lu;%lum"
let &t_8b = "\<Esc>[48;2;%lu;%lu;%lum"
set background=dark
hi! Normal ctermbg=NONE guibg=NONE
