/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:06:16 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/27 19:06:25 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// first 4 bytes COREWAR_EXEC_MAGIC 0xea83f3
// Each character is written to the file as it's ASCII value
//  the name take 128  PROG_NAME_LENGTH eache convert each caracter (dec)to(hexa)
// 4 bytes for NULL 
// champion exic code size 4 bytes.
// champion comment 2048 bytes COMMENT_LENGTH	